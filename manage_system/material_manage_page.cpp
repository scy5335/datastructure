#include "material_manage_page.h"
#include "ui_material_manage_page.h"

material_manage_page::material_manage_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::material_manage_page)
{
    ui->setupUi(this);
<<<<<<< HEAD
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
=======
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
>>>>>>> parent of b97e4d1 (学生课程表界面对接)
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
<<<<<<< HEAD
    QString filename = QFileDialog::getOpenFileName(this, tr("ѡ���ļ�"), "C:/", tr("All files(*.*)"));
=======
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "C:/", tr("All files(*.*)"));
>>>>>>> parent of b97e4d1 (学生课程表界面对接)
    file_path -> setText(filename);
}
