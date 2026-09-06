#!/usr/bin/env bash
#
# install.sh — install / uninstall Machina (binary, icons, desktop entry).
#
# In the release tarball this script sits at the archive root, next to the
# binary and packaging/. In the repository it lives inside packaging/ and
# picks the binary up from build/.
#
# Usage:
#   ./install.sh                # user install to ~/.local (no root needed)
#   sudo ./install.sh           # system-wide install to /usr/local
#   ./install.sh --prefix=DIR   # install to a custom prefix
#   ./install.sh uninstall      # remove a previously installed copy
#                               # (use the same --prefix/--system as before)
#
set -euo pipefail

APP_NAME="machina"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Desktop entry and icons live in packaging/ in the tarball, next to this
# script in the repository.
if [ -d "$SCRIPT_DIR/packaging/icons" ]; then
  ASSETS_DIR="$SCRIPT_DIR/packaging"
else
  ASSETS_DIR="$SCRIPT_DIR"
fi

if [ ! -f "$ASSETS_DIR/$APP_NAME.desktop" ]; then
  echo "error: $APP_NAME.desktop not found in $ASSETS_DIR" >&2
  exit 1
fi

# The binary sits at the archive root in the tarball; fall back to the
# checkout root or build/ when run from the repository.
if [ -x "$SCRIPT_DIR/$APP_NAME" ]; then
  BINARY="$SCRIPT_DIR/$APP_NAME"
elif [ -x "$SCRIPT_DIR/../$APP_NAME" ]; then
  BINARY="$SCRIPT_DIR/../$APP_NAME"
elif [ -x "$SCRIPT_DIR/../build/$APP_NAME" ]; then
  BINARY="$SCRIPT_DIR/../build/$APP_NAME"
else
  echo "error: $APP_NAME binary not found" >&2
  exit 1
fi

MODE="install"
PREFIX=""
SYSTEM=0

print_usage() {
  sed -n '2,10p' "$SCRIPT_DIR/$(basename "${BASH_SOURCE[0]}")" | sed 's/^# \{0,1\}//'
}

while [ $# -gt 0 ]; do
  case "$1" in
    uninstall) MODE="uninstall" ;;
    --system)  SYSTEM=1 ;;
    --prefix=*) PREFIX="${1#*=}" ;;
    -h|--help) print_usage; exit 0 ;;
    *) echo "unknown option: $1 (see --help)" >&2; exit 1 ;;
  esac
  shift
done

if [ -n "$PREFIX" ] && [ "$SYSTEM" -eq 1 ]; then
  echo "--prefix and --system are mutually exclusive" >&2
  exit 1
fi

if [ "$SYSTEM" -eq 1 ]; then
  if [ "$(id -u)" -ne 0 ]; then
    echo "error: --system requires root (run with sudo)" >&2
    exit 1
  fi
  PREFIX="/usr/local"
fi

PREFIX="${PREFIX:-$HOME/.local}"
BIN_DIR="$PREFIX/bin"
DESKTOP_DIR="$PREFIX/share/applications"
ICON_BASE="$PREFIX/share/icons/hicolor"

echo "==> ${MODE^}ing $APP_NAME to $PREFIX"

if [ "$MODE" = "uninstall" ]; then
  rm -fv "$BIN_DIR/$APP_NAME"
  rm -fv "$DESKTOP_DIR/$APP_NAME.desktop"
  for s in 16 32 48 64 128 256 512; do
    rm -fv "$ICON_BASE/${s}x${s}/apps/$APP_NAME.png"
  done
else
  mkdir -p "$BIN_DIR" "$DESKTOP_DIR"

  install -m 755 "$BINARY" "$BIN_DIR/$APP_NAME"
  install -m 644 "$ASSETS_DIR/$APP_NAME.desktop" "$DESKTOP_DIR/"

  for s in 16 32 48 64 128 256 512; do
    icon="$ASSETS_DIR/icons/$APP_NAME-icon-$s.png"
    [ -f "$icon" ] || continue
    mkdir -p "$ICON_BASE/${s}x${s}/apps"
    install -m 644 "$icon" "$ICON_BASE/${s}x${s}/apps/$APP_NAME.png"
  done
fi

# Best-effort refresh so the icon shows up without relogging.
if [ -w "$DESKTOP_DIR" ]; then
  command -v update-desktop-database >/dev/null 2>&1 && \
    update-desktop-database "$DESKTOP_DIR" 2>/dev/null || true
  command -v gtk-update-icon-cache >/dev/null 2>&1 && \
    gtk-update-icon-cache -f "$ICON_BASE" 2>/dev/null || true
fi

if [ "$MODE" = "install" ]; then
  case ":$PATH:" in
    *":$BIN_DIR:"*) ;;
    *) echo "note: $BIN_DIR is not in your PATH — add it to use the launcher entry" ;;
  esac
  echo "==> done. Launch 'machina' from your app menu or terminal."
fi
