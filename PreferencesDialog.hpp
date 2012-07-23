#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include "Preference.hpp"
#include <QtGui>

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    PreferencesDialog(QWidget *parent, const Preference &preference);
    void initialize(void);
};

#endif // PREFERENCESDIALOG_H
