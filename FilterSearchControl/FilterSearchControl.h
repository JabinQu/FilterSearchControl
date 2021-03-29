#ifndef FILTERSEARCHCONTROL_H
#define FILTERSEARCHCONTROL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

class FilterSearchControl : public QWidget
{
    Q_OBJECT
public:
    explicit FilterSearchControl(QWidget *parent = nullptr);
    ~FilterSearchControl();

    void loadData(const QStringList &dataList);

    const QString getString();

signals:
    void signalDeleteItem(QString);

private slots:
    void slotSearchLineEditTextChanged(QString text);
    void slotClearButtonClicked();
    void slotListWidgetClicked(QModelIndex model);
    void slotListWidgetCustonContextMenuReqoested(QPoint pos);
    void slotDeleteListWidgetItem();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    void initListWidgetData(const QStringList &dataList);

private:
    QVBoxLayout *mainVLayout;
    QPushButton *clearButton;
    QLineEdit *searchLineEdit;
    QListWidget *showListWidget;

    QStringList m_dataList;
    QListWidgetItem *selectItem;
};

#endif // FILTERSEARCHCONTROL_H
