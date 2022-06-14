#include "material_manage_page.h"
#include "ui_material_manage_page.h"

material_manage_page::material_manage_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::material_manage_page)
{
    ui->setupUi(this);
    setWindowTitle("资料管理");
    data_name = new QLineEdit();
    search = new QPushButton();
    search -> setText("查询");
    description = new QLineEdit();
    file_select = new QPushButton();
    file_select -> setText("选择文件");
    file_path = new QLabel();
    add_material = new QPushButton();
    add_material -> setText("添加材料");
    material_list = new QTableWidget();
    material_list -> setColumnCount(2);
    material_list -> setHorizontalHeaderLabels(QStringList()<<"选择"<<"材料名称");
    material_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    del_material = new QPushButton();
    del_material -> setText("删除材料");
    material_layout = new QFormLayout();
    material_layout -> addRow("材料描述", description);
    material_layout -> addRow(file_select, file_path);
    material_layout -> addRow(add_material);
    material_layout -> addRow("材料名称", data_name);
    material_layout -> addRow(search);
    material_layout -> addRow(material_list);
    material_layout -> addRow(del_material);
    setLayout(material_layout);
    connect(del_material, &QPushButton::clicked, this, &material_manage_page::try_delete_material);
    connect(add_material, &QPushButton::clicked, this, &material_manage_page::create_new_material);
    connect(file_select, &QPushButton::clicked, this, &material_manage_page::file_select_page);
}

void material_manage_page::initial_set(){
    emit get_all_material();
}

void material_manage_page::set_all_material(QStringList all_material_list){
    int len = all_material_list.length();
    material_list -> clearContents();
    material_list -> setRowCount(len);
    for (int i = 0; i < len; i++){
        QTableWidgetItem *p_check = new QTableWidgetItem();
        p_check -> setCheckState(Qt::Unchecked);
        material_list -> setItem(i, 0, p_check);
        material_list -> setItem(i, 1, new QTableWidgetItem(all_material_list[i]));
    }
}

void material_manage_page::try_delete_material(){
    int row_count = material_list -> rowCount();
    for (int i = 0; i < row_count; i++)
        if (material_list -> item(i, 0) -> checkState() == Qt::Checked)
            emit delete_material(material_list -> item(i, 1) -> text());
    emit get_all_material();
}

void material_manage_page::create_new_material(){
    if (file_path -> text() == "")
        return;
    emit add_new_material(description -> text(),file_path -> text());
    emit get_all_material();
    file_path -> clear();
}

material_manage_page::~material_manage_page()
{
    delete ui;
}

void material_manage_page::file_select_page(){
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "C:/", tr("All files(*.*)"));
    file_path -> setText(filename);
}

void material_manage_page::filter_metarials(){
    emit get_search_result(data_name->text().toLocal8Bit().data());
    data_name -> setText("");
}
