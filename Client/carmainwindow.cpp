#include "carmainwindow.h"

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    result = new ResultDialog();
    measure = new MeasureDialog();
    xmlreader = new XmlReader();

    initUnitCompoBox();
    initSpeedListView();
}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
CarMainWindow::~CarMainWindow()
{
    delete ui;
    delete result;
    delete measure;
    delete xmlreader;
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
  *This slot function is called when ever list view is update. Start-tab view.
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
  *This slot function is called when ever auto start button clicked. Start-tab view.
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
  *This slot function is called when ever list view is update. Start-tab view.
  *@param QString unit.
  */
void CarMainWindow::updateUnitCompoBox(QString unit)
{
    ui->unitComboBox->setCurrentIndex(ui->unitComboBox->findText(unit, Qt::MatchExactly));
}

/**
  *This function is used to init unit combobox. Start-tab view.
  */
void CarMainWindow::initUnitCompoBox()
{
    units << "km/h" << "km" << "h" << "m" << "min" << "Mile" << "Mph" << "in" << "ft" << "yrd";
    ui->unitComboBox->addItems(units);
}

/**
  *This function is used to set items to unit combobox. Start-tab view.
  *@param QStringlist numbers
  */
void CarMainWindow::setUnitCompoBox(QStringList units)
{
    ui->unitComboBox->addItems(units);
}

/**
  *This function is used to init speed listview. Start-tab view.
  */
void CarMainWindow::initSpeedListView()
{
    numbers << "0-40 km/h" << "0-1/4 Mile" << "0-1/8 Mile" << "0-50 km" << "50-100 Mile" << "0-60 Mph" << "0-100 m" << "0-50 ft" << "0-50 yrd" << "0-500 in";
    QAbstractItemModel *model = new StringListModel(numbers);
    ui->listView->setModel(model);
}

/**
  *This function is used to set items to speed listview. Start-tab view.
  *@param QStringlist numbers
  */
void CarMainWindow::setSpeedListView(QStringList numbers)
{
    QAbstractItemModel *model = new StringListModel(numbers);
    ui->listView->setModel(model);
}

/**
  *This function is used to set items to category combobox. Top-tab view.
  *@param
  */
void CarMainWindow::setCategoryCompoBox()
{
    ui->comboBoxTopCategory->addItems(xmlreader->getTop10List());
}

/**
  *This function is used to set items to labelTopList. Top-tab view.
  *@param QString category
  */
void CarMainWindow::setListViewTopList(QString category)
{
    QString topList;

    if (category == "acceleration-0-100")
    {
        topList.append(xmlreader->getTop10AccelerationList());
    }

    else if (category == "Speed")
    {
        topList.append(xmlreader->getTop10SpeedList());
    }

    else if (category == "G-force")
    {
        topList.append(xmlreader->getTop10GforceList());
    }
    ui->labelTopList->setText(topList);
}

/**
  *This slot function is called when speed is achieved in measure dialog. Opens result dialog.
  */
void CarMainWindow::openResultView()
{
    // Show result dialog.
    result->show();
}

/**
  *This slot function is called when ever refresh button clicked. Top-tab view.
  */
void CarMainWindow::on_buttonTopRefresh_clicked()
{
    setCategoryCompoBox();
}

/**
  *This slot function is called when ever category combobox current index changed. Top-tab view.
  *@param QString category
  */
void CarMainWindow::on_comboBoxTopCategory_currentIndexChanged(QString category)
{
    setListViewTopList(category);
}
