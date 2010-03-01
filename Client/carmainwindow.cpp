#include "carmainwindow.h"
#include "ui_carmainwindow.h"
#include "stringlistmodel.h"
#include <QStandardItemModel>
#include <QStringList>
#include <QString>

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    result = new ResultDialog();
    measure = new MeasureDialog();

    initUnitCompoBox();
    initSpeedListView();
}

/**
  *Destructor of this class.  Should be used to release all allocated resources.
  */
CarMainWindow::~CarMainWindow()
{
    delete ui;
}

/**
  *This function is used to .
  *@param
  */
void CarMainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
  *This slot function is called when ever list view is update.
  *@param QModelIndex index.
  */
void CarMainWindow::on_listView_clicked(QModelIndex index)
{
    QString str = index.data().toString();
    QStringList list = str.split("-");
    QStringList list2 = list[1].split(" ");

    ui->minLineEdit->setText(list[0]);
    ui->maxLineEdit->setText(list2[0]);
    updateUnitCompoBox(list2[1]);
}

/**
  *This slot function is called when ever auto start button clicked.
  */
void CarMainWindow::on_autoStartButton_clicked()
{
    if(measure)
    {
        delete measure;
        measure = NULL;
        measure = new MeasureDialog();
    }

    connect(measure, SIGNAL(speedAchieved()), this, SLOT(openResultView()));

    // Show measure dialog.
    measure->show();
}

/**
  *This slot function is called when ever list view is update.
  *@param QString unit.
  */
void CarMainWindow::updateUnitCompoBox(QString unit)
{
    ui->unitComboBox->setCurrentIndex(ui->unitComboBox->findText(unit, Qt::MatchExactly));
}

/**
  *This function is used to init combobox.
  */
void CarMainWindow::initUnitCompoBox()
{
    units << "km/h" << "km" << "h" << "m" << "min" << "mil" << "in" << "ft" << "yrd";
    ui->unitComboBox->addItems(units);
}

/**
  *This function is used to init listview.
  */
void CarMainWindow::initSpeedListView()
{
    numbers << "0-100 km/h" << "0-1/4 mil" << "0-50 km" << "50-100 mil" << "0-100 m" << "0-50 ft" << "0-50 yrd" << "0-500 in";
    QAbstractItemModel *model = new StringListModel(numbers);
    ui->listView->setModel(model);
}

/**
  *This slot function is called when speed is achieved in measure dialog. Opens result dialog.
  */
void CarMainWindow::openResultView()
{
    // Show result dialog.
    result->show();
}
