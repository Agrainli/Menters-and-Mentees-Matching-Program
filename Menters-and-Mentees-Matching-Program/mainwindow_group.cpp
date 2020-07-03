#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::load_group_mentors()
{
    // disconnect(show the original content instead of number. Example gender:male 0 female 1.
    // use disconnect will show word male and female. not use disconnect will show 0 1 2 3 )
    disconnect(ui->checkBox_group_mentor_hall,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    disconnect(ui->checkBox_group_mentor_type,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    disconnect(ui->checkBox_group_mentor_round,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    disconnect(ui->checkBox_group_mentor_gender,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    disconnect(ui->checkBox_group_mentor_special,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    disconnect(ui->checkBox_group_mentor_language,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    disconnect(ui->checkBox_group_mentor_interests,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    disconnect(ui->checkBox_group_mentor_academic_info,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);

    // mentors to be grouped

    // clear exist data(model_mentors is a private pointer)
    if ( model_group_mentors_to_be_grouped != nullptr )
    {
        delete model_group_mentors_to_be_grouped;
        model_group_mentors_to_be_grouped = nullptr;
    }

    // link db to mentors QSqlTableModel(db to QSqlTableModel)
    model_group_mentors_to_be_grouped = new QSqlTableModel(this,db);    // model_mentors is a private pointer defined in header file
    model_group_mentors_to_be_grouped->setTable("mentor");
    model_group_mentors_to_be_grouped->setEditStrategy(QSqlTableModel::OnFieldChange);
    model_group_mentors_to_be_grouped->setFilter("group_id=0 AND wwvp<>'' AND wwvp<>'n' AND train_complete='y'");
    model_group_mentors_to_be_grouped->select();
    while(model_group_mentors_to_be_grouped->canFetchMore()){
        model_group_mentors_to_be_grouped->fetchMore();
    }

    // link mentors QSqlTableModel to QTableView(QSqlTableModel to QTableView)
    ui->tableView_group_mentor_to_be_group->setModel(model_group_mentors_to_be_grouped);
    ui->tableView_group_mentor_to_be_group->reset();
    ui->tableView_group_mentor_to_be_group->horizontalHeader()->setMaximumSectionSize(400);
    ui->tableView_group_mentor_to_be_group->setSortingEnabled(true);

    //the right window select behaviour
    ui->tableView_group_mentor_to_be_group->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_group_mentor_to_be_group->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // delegate(The function of delegate is to decide show number or specific name)
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(1,delegate_yes_no);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(17,delegate_yes_no);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(18,delegate_yes_no);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(19,delegate_yes_no);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(20,delegate_yes_no);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(6,delegate_round);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(7,delegate_academic_level);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(10,delegate_type);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(11,delegate_gender);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(12,delegate_language);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(8,delegate_college);
    ui->tableView_group_mentor_to_be_group->setItemDelegateForColumn(15,delegate_special_mentors);

    // resize row height according to column width
    ui->tableView_group_mentor_to_be_group->resizeColumnsToContents();
    ui->tableView_group_mentor_to_be_group->resizeRowsToContents();

    // hide columns
    ui->tableView_group_mentor_to_be_group->hideColumn(0);//group ID
    ui->tableView_group_mentor_to_be_group->hideColumn(1);//is_confirmed
    ui->tableView_group_mentor_to_be_group->hideColumn(5);//wwvp
    ui->tableView_group_mentor_to_be_group->hideColumn(17);//train_1
    ui->tableView_group_mentor_to_be_group->hideColumn(18);//train_2
    ui->tableView_group_mentor_to_be_group->hideColumn(19);//train_3
    ui->tableView_group_mentor_to_be_group->hideColumn(20);//train

    //--------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------

    // mentors grouped

    // clear exist data
    if ( model_group_mentors_grouped != nullptr )
    {
        delete model_group_mentors_grouped;
        model_group_mentors_grouped = nullptr;
    }

    // link db to mentors QSqlTableModel
    model_group_mentors_grouped = new my_QSqlTableModel_Grouping(this,db);    // model_mentors is a private pointer defined in header file
    model_group_mentors_grouped->setTable("mentor");
    model_group_mentors_grouped->setEditStrategy(QSqlTableModel::OnFieldChange);
    model_group_mentors_grouped->setFilter("group_id<>0 AND wwvp<>'' AND wwvp<>'n' AND train_complete='y'");
    model_group_mentors_grouped->select();
    while(model_group_mentors_grouped->canFetchMore()){
        model_group_mentors_grouped->fetchMore();
    }

    // link mentors QSqlTableModel to QTableView
    ui->tableView_group_mentor_grouped->setModel(model_group_mentors_grouped);
    ui->tableView_group_mentor_grouped->reset();
    ui->tableView_group_mentor_grouped->horizontalHeader()->setMaximumSectionSize(400);
    ui->tableView_group_mentor_grouped->sortByColumn(0,Qt::AscendingOrder);

    ui->tableView_group_mentor_grouped->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView_group_mentor_grouped->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView_group_mentor_grouped->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // delegate
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(1,delegate_yes_no);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(17,delegate_yes_no);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(18,delegate_yes_no);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(19,delegate_yes_no);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(20,delegate_yes_no);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(6,delegate_round);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(7,delegate_academic_level);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(10,delegate_type);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(11,delegate_gender);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(12,delegate_language);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(8,delegate_college);
    ui->tableView_group_mentor_grouped->setItemDelegateForColumn(15,delegate_special_mentors);

    // resize row height according to column width
    ui->tableView_group_mentor_grouped->resizeColumnsToContents();
    ui->tableView_group_mentor_grouped->resizeRowsToContents();
    //connect(ui->tableView_group_mentor_grouped->horizontalHeader(),&QHeaderView::sectionResized,
    //        ui->tableView_group_mentor_grouped,&QTableView::resizeRowsToContents);

    // hide columns
    ui->tableView_group_mentor_grouped->hideColumn(0);
    ui->tableView_group_mentor_grouped->hideColumn(1);
    ui->tableView_group_mentor_grouped->hideColumn(5);
    ui->tableView_group_mentor_grouped->hideColumn(17);
    ui->tableView_group_mentor_grouped->hideColumn(18);
    ui->tableView_group_mentor_grouped->hideColumn(19);
    ui->tableView_group_mentor_grouped->hideColumn(20);

    /*
    ui->tableView_group_mentor_grouped->setEditTriggers(QAbstractItemView::NoEditTriggers);
    */

    // connect(connect ui->checkBox_mentors to QCheckBox)
    connect(ui->checkBox_group_mentor_hall,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    connect(ui->checkBox_group_mentor_type,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    connect(ui->checkBox_group_mentor_round,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    connect(ui->checkBox_group_mentor_gender,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    connect(ui->checkBox_group_mentor_special,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    connect(ui->checkBox_group_mentor_language,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    connect(ui->checkBox_group_mentor_interests,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
    connect(ui->checkBox_group_mentor_academic_info,&QCheckBox::stateChanged,this,&MainWindow::display_group_column);
}

// Grouped mentor search(It is a function in the left below)
void MainWindow::on_lineEdit_group_mentor_grouped_search_editingFinished()
{
    QString str = ui->lineEdit_group_mentor_grouped_search->text().simplified();    // Returns a string that has whitespace removed from the start and the end
    QString argument = "group_id<>0 AND wwvp<>'' AND wwvp<>'n' AND train_complete='y'";
    if(str.isEmpty()) {
        model_group_mentors_grouped->setFilter(argument);
        return;
    }

    QStringList list = str.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);   // get string list
    for (int i=0; i < list.size() ; i++)
    {
        QString tmp = list.at(i);
        argument = argument + QString(" AND ( uid LIKE \'%%1%\' OR first_name LIKE '%%2%' OR last_name LIKE '%%3%' )").arg(tmp).arg(tmp).arg(tmp);       // Uni ID + First Name + Last Name
        //qDebug() << argument;
    }
    model_group_mentors_grouped->setFilter(argument);
}



// To be grouped mentor search(It is a function in the right below)
void MainWindow::on_lineEdit_group_mentor_to_be_group_search_editingFinished()
{
    QString str = ui->lineEdit_group_mentor_to_be_group_search->text().simplified();    // Returns a string that has whitespace removed from the start and the end
    QString argument = "group_id=0 AND wwvp<>'' AND wwvp<>'n' AND train_complete='y'";
    if(str.isEmpty()) {
        model_group_mentors_to_be_grouped->setFilter(argument);
        return;
    }

    QStringList list = str.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);   // get string list
    for (int i=0; i < list.size() ; i++)
    {
        QString tmp = list.at(i);
        argument = argument + QString(" AND ( uid LIKE \'%%1%\' OR first_name LIKE '%%2%' OR last_name LIKE '%%3%' )").arg(tmp).arg(tmp).arg(tmp);       // Uni ID + First Name + Last Name
        //qDebug() << argument;
    }
    model_group_mentors_to_be_grouped->setFilter(argument);
}

// Add to Group(get the mentor from the right side and remove it into the left side)
void MainWindow::on_toolButton_left_clicked()
{
    QItemSelectionModel * selections_grouped = ui->tableView_group_mentor_grouped->selectionModel();
    QModelIndexList selected_grouped = selections_grouped->selectedRows();

    int group_id = -1;
    if ( selected_grouped.isEmpty() )
    {
        QSqlQueryModel querymodel;
        querymodel.setQuery("SELECT MAX(group_id) FROM mentor",db);
        while(querymodel.canFetchMore()){
            querymodel.fetchMore();
        }
        int max_group_id = querymodel.record(0).value(0).toInt();
        group_id = max_group_id+1;
    }
    else
    {
        int row = selected_grouped.at(0).row();
        group_id = model_group_mentors_grouped->record(row).value("group_id").toInt();
    }

    QItemSelectionModel * selections = ui->tableView_group_mentor_to_be_group->selectionModel();
    QModelIndexList selected = selections->selectedRows();
    foreach(QModelIndex selectedIndex, selected)
    {
        int row = selectedIndex.row();
        QSqlRecord r = model_group_mentors_to_be_grouped->record(row);
        r.setValue("group_id",group_id);
        model_group_mentors_to_be_grouped->setRecord(row,r);
    }

    model_group_mentors_to_be_grouped->select();
    model_group_mentors_grouped->select();

    ui->tableView_group_mentor_grouped->resizeColumnsToContents();
    ui->tableView_group_mentor_grouped->resizeRowsToContents();

    ui->tableView_group_mentor_to_be_group->resizeColumnsToContents();
    ui->tableView_group_mentor_to_be_group->resizeRowsToContents();
}

// Remove from group(get the mentor from the left side and remove it into the left side)
void MainWindow::on_toolButton_right_clicked()
{
    QItemSelectionModel * selections = ui->tableView_group_mentor_grouped->selectionModel();
    QModelIndexList selected = selections->selectedRows();
    foreach(QModelIndex selectedIndex, selected)
    {
        int row = selectedIndex.row();
        QSqlRecord r = model_group_mentors_grouped->record(row);
        r.setValue("group_id",0);
        model_group_mentors_grouped->setRecord(row,r);
    }
    model_group_mentors_to_be_grouped->select();
    model_group_mentors_grouped->select();

    // re-arrange group-id
    QSqlQueryModel querymodel;
    QSqlQuery query(db);

    // get max group_id
    querymodel.setQuery("SELECT MAX(group_id) FROM mentor",db);
    while(querymodel.canFetchMore()){
        querymodel.fetchMore();
    }
    int max_group_id = querymodel.record(0).value(0).toInt();

    if (max_group_id == 0)
        return;

    int minus_num = 0;
    for (int current_id = 1; current_id <= max_group_id; current_id++)
    {
        querymodel.setQuery(QString("SELECT uid from mentor WHERE group_id=%1").arg(current_id),db);
        while(querymodel.canFetchMore()){
            querymodel.fetchMore();
        }

        if ( querymodel.rowCount()==0 )     // a group doesn't have any menber
        {
            minus_num++;
        }

        for (int i = 0; i < querymodel.rowCount(); i++)
        {
            QVariant uid = querymodel.record(i).value("uid");
            query.exec(QString("UPDATE mentor SET group_id=%1 WHERE uid=\'%2\'").arg(QVariant(current_id-minus_num).toString()).arg(uid.toString()));
        }
    }

    model_group_mentors_to_be_grouped->select();
    model_group_mentors_grouped->select();

    ui->tableView_group_mentor_grouped->resizeColumnsToContents();
    ui->tableView_group_mentor_grouped->resizeRowsToContents();

    ui->tableView_group_mentor_to_be_group->resizeColumnsToContents();
    ui->tableView_group_mentor_to_be_group->resizeRowsToContents();
}

//auto group mentor event(call the algorithm_mentors_group()function)
void MainWindow::on_pushButton_mentor_auto_clicked()
{
    algorithm_mentors_group();
    model_group_mentors_to_be_grouped->select();
    model_group_mentors_grouped->select();

    ui->tableView_group_mentor_grouped->resizeColumnsToContents();
    ui->tableView_group_mentor_grouped->resizeRowsToContents();

    ui->tableView_group_mentor_to_be_group->resizeColumnsToContents();
    ui->tableView_group_mentor_to_be_group->resizeRowsToContents();
}

//clear all the mentors in the lift side and remove them to the right side
void MainWindow::on_pushButton_mentor_clear_clicked()
{
    QSqlQuery query(db);
    query.exec("UPDATE mentor SET group_id=0");
    query.exec("UPDATE mentee SET group_id=0");
    model_group_mentors_to_be_grouped->select();
    model_group_mentors_grouped->select();

    ui->tableView_group_mentor_grouped->resizeColumnsToContents();
    ui->tableView_group_mentor_grouped->resizeRowsToContents();

    ui->tableView_group_mentor_to_be_group->resizeColumnsToContents();
    ui->tableView_group_mentor_to_be_group->resizeRowsToContents();
}

//show each mentors column according to tickbox
void MainWindow::display_group_column()
{
    // round
    if (ui->checkBox_group_mentor_round->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(6);
        ui->tableView_group_mentor_to_be_group->showColumn(6);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(6);
        ui->tableView_group_mentor_to_be_group->hideColumn(6);
    }

    // academic info
    if (ui->checkBox_group_mentor_academic_info->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(7);
        ui->tableView_group_mentor_grouped->showColumn(8);
        ui->tableView_group_mentor_grouped->showColumn(9);
        ui->tableView_group_mentor_to_be_group->showColumn(7);
        ui->tableView_group_mentor_to_be_group->showColumn(8);
        ui->tableView_group_mentor_to_be_group->showColumn(9);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(7);
        ui->tableView_group_mentor_grouped->hideColumn(8);
        ui->tableView_group_mentor_grouped->hideColumn(9);
        ui->tableView_group_mentor_to_be_group->hideColumn(7);
        ui->tableView_group_mentor_to_be_group->hideColumn(8);
        ui->tableView_group_mentor_to_be_group->hideColumn(9);
    }

    // type
    if (ui->checkBox_group_mentor_type->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(10);
        ui->tableView_group_mentor_to_be_group->showColumn(10);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(10);
        ui->tableView_group_mentor_to_be_group->hideColumn(10);
    }

    // gender
    if (ui->checkBox_group_mentor_gender->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(11);
        ui->tableView_group_mentor_to_be_group->showColumn(11);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(11);
        ui->tableView_group_mentor_to_be_group->hideColumn(11);
    }

    // language
    if (ui->checkBox_group_mentor_language->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(12);
        ui->tableView_group_mentor_grouped->showColumn(13);
        ui->tableView_group_mentor_to_be_group->showColumn(12);
        ui->tableView_group_mentor_to_be_group->showColumn(13);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(12);
        ui->tableView_group_mentor_grouped->hideColumn(13);
        ui->tableView_group_mentor_to_be_group->hideColumn(12);
        ui->tableView_group_mentor_to_be_group->hideColumn(13);
    }

    // hall
    if (ui->checkBox_group_mentor_hall->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(14);
        ui->tableView_group_mentor_to_be_group->showColumn(14);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(14);
        ui->tableView_group_mentor_to_be_group->hideColumn(14);
    }

    // special
    if (ui->checkBox_group_mentor_special->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(15);
        ui->tableView_group_mentor_to_be_group->showColumn(15);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(15);
        ui->tableView_group_mentor_to_be_group->hideColumn(15);
    }

    // interests
    if (ui->checkBox_group_mentor_interests->isChecked())
    {
        ui->tableView_group_mentor_grouped->showColumn(16);
        ui->tableView_group_mentor_to_be_group->showColumn(16);
    }
    else
    {
        ui->tableView_group_mentor_grouped->hideColumn(16);
        ui->tableView_group_mentor_to_be_group->hideColumn(16);
    }
}


