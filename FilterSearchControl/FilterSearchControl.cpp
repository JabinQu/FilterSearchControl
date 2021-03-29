#include "FilterSearchControl.h"
#include <QMessageBox>
#include <QMenu>
#include <QAction>

FilterSearchControl::FilterSearchControl(QWidget *parent) : QWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);
    setLayout(mainVLayout);

    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText(tr("Currently drawn"));
    showListWidget = new QListWidget(this);
    showListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    clearButton = new QPushButton ("x", this);

    mainVLayout->addWidget(searchLineEdit);
    mainVLayout->addWidget(showListWidget);

    connect(searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotSearchLineEditTextChanged(QString)));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(slotClearButtonClicked()));
    connect(showListWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(slotListWidgetClicked(QModelIndex)));
    connect(showListWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotListWidgetCustonContextMenuReqoested(QPoint)));
}

FilterSearchControl::~FilterSearchControl()
{
    selectItem = NULL;
}

void FilterSearchControl::loadData(const QStringList &dataList)
{
    if (dataList.isEmpty())
        return;
    m_dataList = dataList;
    initListWidgetData(dataList);
}

const QString FilterSearchControl::getString()
{
    QString str = "";
    QListWidgetItem *item = showListWidget->currentItem();
    if (item && item->checkState() == Qt::Checked)
        str = showListWidget->currentItem()->text();
    else if (selectItem != NULL)
    {
        str = selectItem->text();
    }
    return str;
}

void FilterSearchControl::slotSearchLineEditTextChanged(QString text)
{
    QStringList dataList;
    if (text.isEmpty())
    {
        dataList = m_dataList;
    }
    else
    {
        foreach (QString str, m_dataList) {
            if (str.contains(text) || str == text)
                dataList.append(str);
        }
    }
    initListWidgetData(dataList);
}

void FilterSearchControl::slotClearButtonClicked()
{
    searchLineEdit->clear();
}

void FilterSearchControl::slotListWidgetClicked(QModelIndex model)
{
    QListWidgetItem *item = showListWidget->item(model.row());
    if (!item)
        return;
    if (item->checkState() == Qt::Checked)
        return;
    item->setCheckState(Qt::Checked);
    selectItem = item;

    for (int i = showListWidget->count()-1; i >= 0; i--)
    {
        if (showListWidget->item(i) == showListWidget->item(model.row()))
            continue;
        showListWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

void FilterSearchControl::slotListWidgetCustonContextMenuReqoested(QPoint pos)
{
    QListWidgetItem* curItem = showListWidget->itemAt( pos);
    if(curItem == NULL)
        return;
    if (curItem->checkState() != Qt::Checked)
        return;

    QMenu *popMenu = new QMenu(showListWidget);
    QAction *deleteAction = new QAction(tr("Delete"), this);
    popMenu->addAction(deleteAction);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(slotDeleteListWidgetItem()));
    popMenu->exec(QCursor::pos());
    delete popMenu;
    delete deleteAction;
}

void FilterSearchControl::slotDeleteListWidgetItem()
{
    int ret = QMessageBox::warning(this, tr("Warning"),
                                   tr("Are you sure to delete this item?"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::No);

    if (ret != QMessageBox::Yes)
        return;

    QListWidgetItem *item = showListWidget->currentItem();
    if(!item)
        return;

    emit signalDeleteItem(item->text());
    m_dataList.removeOne(item->text());

    int curIndex = showListWidget->row(item);
    showListWidget->takeItem(curIndex);
    delete item;
    selectItem = NULL;
    showListWidget->setCurrentItem(NULL);
}

void FilterSearchControl::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    clearButton->setFixedSize(searchLineEdit->height()-4, searchLineEdit->height()-4);
    clearButton->move(searchLineEdit->pos().x()+searchLineEdit->width()-searchLineEdit->height()+2,
                      searchLineEdit->pos().y()+2);
}

void FilterSearchControl::initListWidgetData(const QStringList &dataList)
{
    showListWidget->clear();
    if (dataList.isEmpty())
        return;
    selectItem = NULL;
    QListWidgetItem *item;
    foreach (QString str, dataList) {
        item = new QListWidgetItem(str);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Unchecked);
        showListWidget->addItem(item);
    }
}
