#include "material_manage_page.h"
#include "ui_material_manage_page.h"

material_manage_page::material_manage_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::material_manage_page)
{
    ui->setupUi(this);
    setWindowTitle("���Ϲ���");
    description = new QLineEdit();
    file_select = new QPushButton();
    file_select -> setText("ѡ���ļ�");
    file_path = new QLabel();
    add_material = new QPushButton();
    add_material -> setText("���Ӳ���");
    material_list = new QListWidget();
    del_material = new QPushButton();
    del_material -> setText("ɾ������");
    material_layout = new QFormLayout();
    material_layout -> addRow("��������", description);
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
    QString filename = QFileDialog::getOpenFileName(this, tr("ѡ���ļ�"), "C:/", tr("All files(*.*)"));
    file_path -> setText(filename);
}

