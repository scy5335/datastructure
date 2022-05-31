#ifndef MYGRAPHVIEW_H
#define MYGRAPHVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QTimeLine>
#include <QEasingCurve>
#include <fstream>
#include <QVector>
#include <QApplication>
#include <QTime>
#include <random>
#include <cstring>
#include <cmath>
#include "trie.h"

class myGraphVectex;
class myGraphView;
class myGraphEdge;
class graph;

class myGraphView:public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene* myGraphicsScene;
    myGraphVectex* addVec(QPointF center, QString name, qreal radius=10, int vx = 0);
    void addLine(myGraphVectex* start, myGraphVectex* end);
    void GetNewNarrow(int line_base);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool onLeftbotton = 0;
    QVector<myGraphVectex*> vexes;
    QVector<myGraphEdge*> line;
    int VecCnt = 0, EdgeCnt = 0;
    qreal zValue = -1;
    double dis(double x1, double y1, double x2, double y2);

signals:
    void mouseLeftClicked(QPointF position);
    void mouseReleased();
    void selected(int id);

public:
    myGraphView();
    void SaveToFile();
    void ReadFromFile(std::string file_name, int vx, int vy, int ex, int ey);
    QStringList GetVecName();
    static graph *maingraph;
};

class myGraphVectex:public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

private:
    static unsigned int VecCount;
    QBrush regBrush = QBrush(QColor(58, 143, 192));
    QBrush selBrush = QBrush(QColor(208, 90, 110));
    QBrush currentBrush = QBrush(QColor(0, 137, 108));
    int base;
    QPointF center;
    qreal radius;

    QGraphicsSimpleTextItem *nameTag = nullptr;
    QString nameText = "";
    QFont nameFont = QFont("Corbel", 11, QFont::Normal, true);
    QGraphicsSimpleTextItem *nowpos = nullptr;
    QString hintText = "";
    QFont hintFont = QFont("Corbel", 10);
    bool beSelected = false;

    void onLeftClick(QPointF position);
    void releaseffect();

signals:
    void selected(int id);

public:
    int id;
    myGraphVectex(QPointF _center, qreal _r, QString name, int nameID = 0, QGraphicsItem *parent = nullptr);
    void estconnect(myGraphView *view);
    void showAnimation();
    qreal getRadius() {return radius;}
    QString getData(){return QString::asprintf("%g %g %g\n", center.x(), center.y(), radius);}
    QString GetName();
    double getX(){return center.x();}
    double getY(){return center.y();}
};

class myGraphEdge : public QObject, public QGraphicsLineItem{
    Q_OBJECT

private:
    static int EdgeNum;
    myGraphVectex *startVex;
    myGraphVectex *endVex;
    QGraphicsLineItem *line = nullptr;

    int Narrow;

    qreal lineWidth = 3;
    Qt::PenStyle lineStyle = Qt::SolidLine;
    Qt::PenCapStyle capStyle = Qt::RoundCap;
    QColor defaultColor = QColor(125, 185, 222);
    QColor smoothColor = QColor(50, 205, 50);
    QColor normalColor = QColor(255, 215, 0);
    QColor crowdColor = QColor(238, 0, 0);
    QPen defaultPen;
    QPen curPen;
    QFont textFont = QFont("Corbel", 12);
    QColor textColor = QColor(0, 0, 0);

    qreal angle = 0;
    QPointF center;
    QPointF sP, eP, dP;

    void setLengthRate(qreal r=1);
    void drawLine();
    void drawText();
    void setText();

public:

    myGraphEdge(myGraphVectex *start, myGraphVectex *end, QGraphicsItem *parent = nullptr);
    void refreshLine();
    int ReflashNarrow();
};

struct Edge{
    int last, to;
    int narrow = 0;
    double len;
};

class graph{
private:
    const static int max_vec = 55;
    constexpr static double onfootspeed = 10.0;
    constexpr static double bicyclespeed = 50.0;
    int VecNum = 0, EdgeNum = 1;
    int head[max_vec];
    char name[max_vec][105];
    Edge e[405];
    trie graphtrie;
    double dis[max_vec];
    bool vis[max_vec];
    int lastpos[max_vec];
    QStringList dijkstra(int st, int ed, double &totminutes, int mod);
    QString select_route(double &totminutes, int hour, int minute);
    int hour[8];
    int minute[8];

public:
    void create_time_table();
    QStringList FindPath(QStringList guide_list, double &totminutes, int mod, int hour, int minute);
    void addVec(char* S);
    void addEdge(int start,int end, double len);
    void resetnarrow(int* narrowlist, int num, int line_base);
};

#endif // MYGRAPHVIEW_H
