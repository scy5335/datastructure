#include "material_manage_page.h"
#include "ui_material_manage_page.h"

material_manage_page::material_manage_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::material_manage_page)
{
    ui->setupUi(this);
    setWindowTitle("资料管理");
    description = new QLineEdit();
    file_select = new QPushButton();
    file_select -> setText("选择文件");
    file_path = new QLabel();
    add_material = new QPushButton();
    add_material -> setText("添加材料");
    material_list = new QListWidget();
    del_material = new QPushButton();
    del_material -> setText("删除材料");
    material_layout = new QFormLayout();
    material_layout -> addRow("材料描述", description);
    material_layout -> addRow(file_select, file_path);
    material_layout -> addRow(add_material);
    material_layout -> addRow(material_list);
    material_layout -> addRow(del_material);
    setLayout(material_layout);
    connect(file_select, &QPushButton::clicked, this, &material_manage_page::file_select_page);
}

material_manage_page::~material_manage_page()
{
    delete ui;
}

void material_manage_page::file_select_page(){
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "C:/", tr("All files(*.*)"));
    file_path -> setText(filename);
}
