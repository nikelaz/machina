#include "ProcessModel.h"

ProcessModel::ProcessModel(
    std::vector<process_reader::Process> processes,
    QObject* parent
)
  : QAbstractListModel(parent),
    m_processes(std::move(processes))
{
}

int ProcessModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return static_cast<int>(m_processes.size());
}

QVariant ProcessModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || index.row() >= static_cast<int>(m_processes.size()))
  {
    return {};
  }

  const auto& proc = m_processes[index.row()];

  switch (role)
  {
    case PidRole:
      return QString::fromStdString(proc.pid);
    case NameRole:
      return QString::fromStdString(proc.name);
    default:
      return {};
  }
}

QHash<int, QByteArray> ProcessModel::roleNames() const
{
  return {
    { PidRole, "pid" },
    { NameRole, "name" }
  };
}
