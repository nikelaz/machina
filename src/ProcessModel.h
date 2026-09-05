#pragma once

#include <QAbstractListModel>
#include "ProcessReader.h"

class ProcessModel : public QAbstractListModel
{
  Q_OBJECT

private:
  std::vector<process_reader::Process> m_processes;

public:
  enum Roles
  {
    PidRole = Qt::UserRole + 1,
    NameRole
  };

  ProcessModel(
    std::vector<process_reader::Process> processes,
    QObject* parent = nullptr
  );

  int rowCount(const QModelIndex& parent = {}) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;
};
