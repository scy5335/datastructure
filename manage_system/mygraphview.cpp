#include "mygraphview.h"

using namespace std;

graph* myGraphView::maingraph = NULL;

myGraphView::myGraphView()
{
    this->setMouseTracking(true);
    this->setBackgroundBrush(Qt::transparent);
    myGraphicsScene = new QGraphicsScene();
    this->setScene(myGraphicsScene);
    this->setRenderHint(QPainter::Antialiasing);
    this->setCursor(Qt::CrossCursor);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    QTime randomTime;
    randomTime = QTime::currentTime();
    srand(randomTime.msec()+randomTime.second()*1000);
}

void myGraphView::mousePressEvent(QMouseEvent *event)
{
    if (event -> button() == Qt::LeftButton){
        onLeftbotton = 1;
        emit mouseLeftClicked(mapToScene(event->pos()));
        //addVec(mapToScene(event->pos()), "test");
    }
}

void myGraphView::mouseReleaseEvent(QMouseEvent *event)
{
    if (onLeftbotton){
        onLeftbotton = 0;
        emit mouseReleased();
    }
}

void graph::create_time_table(){
    hour[0]=6; minute[0]=30;
    hour[0]=9; minute[0]=50;
    hour[0]=12; minute[0]=30;
    hour[0]=15; minute[0]=50;
    hour[0]=18; minute[0]=30;
    hour[0]=21; minute[0]=00;
}

myGraphVectex* myGraphView::addVec(QPointF center, QString name, qreal radius, int vx)
{
    myGraphVectex* newvec = new myGraphVectex(center, radius, name);
    this -> scene() -> addItem(newvec);
    vexes.push_back(newvec);
    newvec -> estconnect(this);
    newvec -> showAnimation();
    return newvec;
}

void myGraphView::addLine(myGraphVectex *start, myGraphVectex *end){
    myGraphEdge *newLine = new myGraphEdge(start, end);
    scene()->addItem(newLine);
    line.push_back(newLine);
    newLine->refreshLine();
    newLine->setZValue(--zValue);
}

void myGraphVectex::showAnimation(){
    QTimeLine *timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(0, 200);
    QEasingCurve curve = QEasingCurve::OutBounce;
    qreal baseRadius = this->rect().width() / 2;
    qreal difRadius = radius - baseRadius;
    connect(timeLine, &QTimeLine::frameChanged, timeLine, [=](int frame){
        qreal curProgress = curve.valueForProgress(frame / 200.0);
        qreal curRadius = baseRadius + difRadius * curProgress;
        this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
    });
    timeLine->start();
}

void myGraphView::SaveToFile(){
    //vexes
    fstream ts("map.txt", ios::out);
    ts << vexes.size() << "\n";
    for(int i = 0; i < vexes.size(); i++){
        ts << (vexes[i]->getData()).toStdString();
    }
    ts.close();
}

void myGraphView::ReadFromFile(string file_name, int vx, int vy, int ex, int ey){
    //vexes
    fstream ts(file_name, ios::in);
    ts >> VecCnt;
    int x,y,r;
    char S[105];
    for (int i = 0; i < VecCnt; i++){
        ts>>x>>y>>r>>S;
        addVec(QPointF(x, y), QString::fromStdString(S), r, vx);
        maingraph -> addVec(S);
    }
    ts >> EdgeCnt;
    for (int i = 0; i < EdgeCnt; i++){
        ts>>x>>y;
        addLine(vexes[x], vexes[y]);
        maingraph -> addEdge(x + 1 + vx, y + 1 + vx,
                             dis(vexes[x]->getX(), vexes[x]->getY(),
                                 vexes[y]->getX(), vexes[y]->getY()));
    }
    GetNewNarrow(ex);
    ts.close();
}

double myGraphView::dis(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void myGraphView::GetNewNarrow(int line_base){
    int *NarrowList = new int[line.size()];
    for (int i=0; i < line.size(); i++)
        NarrowList[i] = line[i]->ReflashNarrow();
    maingraph -> resetnarrow(NarrowList, line.size(), line_base);
    delete[] NarrowList;
}

QStringList myGraphView::GetVecName(){
    QStringList NameList;
    for (int i = 0; i < vexes.size(); i++)
        NameList << vexes[i]->GetName();
    return NameList;
}

unsigned int myGraphVectex::VecCount=0;

myGraphVectex::myGraphVectex(QPointF _center, qreal _r, QString name, int nameID, QGraphicsItem *parent)
    :QGraphicsEllipseItem(_center.x() - 0.5, _center.y() - 0.5, 1, 1, parent),
    center(_center),
    radius(_r)
{
    id = VecCount++;
    nameText = name;
    nameTag = new QGraphicsSimpleTextItem;
    nameTag->setPos(center - QPointF(2*radius, radius));
    nameTag->setFont(nameFont);
    nameTag->setText(nameText);
    nameTag->setZValue(this->zValue());
    this->setPen(Qt::NoPen);
    this->setBrush(regBrush);
}

void myGraphVectex::estconnect(myGraphView *view)
{
    view -> scene() -> addItem(nameTag);
    connect(view, &myGraphView::mouseLeftClicked, this, &myGraphVectex::onLeftClick);
    connect(view, &myGraphView::mouseReleased, this, &myGraphVectex::releaseffect);
    connect(this, &myGraphVectex::selected, view, &myGraphView::selected);
}

void myGraphVectex::onLeftClick(QPointF position){
    if (this -> contains(position))
        beSelected = 1;
    else beSelected = 0;
}

void myGraphVectex::releaseffect(){
    if (beSelected)
        emit selected(id);
}

QString myGraphVectex::GetName(){
    return nameText;
}

myGraphEdge::myGraphEdge(myGraphVectex *start, myGraphVectex *end, QGraphicsItem *parent):
    QGraphicsLineItem(parent),
    startVex(start),
    endVex(end){
    defaultPen.setWidth(lineWidth);
    defaultPen.setStyle(lineStyle);
    defaultPen.setCapStyle(capStyle);
    defaultPen.setColor(defaultColor);
    curPen = defaultPen;
}

void myGraphEdge::refreshLine(){
    setLengthRate(1);
    drawLine();
}

void myGraphEdge::setLengthRate(qreal r){
    sP = startVex->scenePos() + startVex->rect().center();
    eP = endVex->scenePos() + endVex->rect().center();
    dP = eP - sP;
    angle = atan2(dP.y(), dP.x());
    eP -= QPointF(endVex->getRadius() * cos(angle), endVex->getRadius() * sin(angle));
    sP += QPointF(endVex->getRadius() * cos(angle), endVex->getRadius() * sin(angle));
    dP = (eP - sP) * r;
    eP = sP + dP;
}

void myGraphEdge::drawLine(){
    this->setLine(sP.x(), sP.y(), eP.x(), eP.y());
    QPen bgPen;
    bgPen.setColor(QColor(255, 255, 255, 0));
    bgPen.setWidth(lineWidth + 5);
    this->setPen(bgPen);

    if(line){
        scene()->removeItem(line);
        line = nullptr;
    }

    center = (startVex->scenePos() + startVex->rect().center() + endVex->scenePos() + endVex->rect().center())/2;

    QGraphicsLineItem *newLine = new QGraphicsLineItem(sP.x(), sP.y(), eP.x(), eP.y());
    newLine->setPen(curPen);
    newLine->setZValue(this->zValue() - 1);
    this->scene()->addItem(newLine);
    line = newLine;
}

int myGraphEdge::ReflashNarrow(){
    Narrow = rand() % 100;
    if (Narrow <40)
        curPen.setColor(smoothColor);
    else if (Narrow < 80)
        curPen.setColor(normalColor);
    else curPen.setColor(crowdColor);
    refreshLine();
    return Narrow;
}

void graph::addVec(char *S){
    VecNum++;
    memcpy(name[VecNum], S, sizeof(name[VecNum]));
    graphtrie.addstring(S, VecNum);
    //qDebug()<<S;
}

void graph::addEdge(int start, int end, double len){
    e[EdgeNum].to = end; e[EdgeNum].last = head[start]; e[EdgeNum].len = len; head[start] = EdgeNum++;
    e[EdgeNum].to = start; e[EdgeNum].last = head[end]; e[EdgeNum].len = len; head[end] = EdgeNum++;
}

QStringList graph::FindPath(QStringList guide_list, double &totminutes, int mod, int hour, int minute){
    int list[15];
    int size = guide_list.size();
    if (size <= 1) return guide_list;
    QStringList result_list;
    for (int i = 0; i < size; i++)
        list[i] = graphtrie.findid(guide_list[i].toStdString().c_str());
    result_list << QString::fromStdString(name[list[0]]);
    for (int i = 1; i < size; i++){
        if ((list[i] < 26 && list[i-1] < 26)||(list[i] >= 26 && list[i-1] >= 26))
            result_list += dijkstra(list[i], list[i-1], totminutes, mod);
        else {
            result_list += select_route(totminutes, hour, minute);
            result_list += QString::fromStdString(name[list[i]]);
        }
    }
    return result_list;
}

QString graph::select_route(double &totminutes, int hour, int minute){
    int school_bus_time, i, vehicle_time;
    for (i = 0; i < 6; i++)
        if (hour < this -> hour[i] || (hour == this->hour[i] && minute <= this -> minute[i]))
            break;
    if (i == 6){
        if (hour <= 6)
            school_bus_time = (this -> hour[0] - hour) * 60 + this -> minute[0] - minute + 60;
        else
            school_bus_time = (this -> hour[0] + 24 - hour) * 60 + this -> minute[0] - minute + 60;
    }
    else
        school_bus_time = (this -> hour[i] - hour) * 60 + this -> minute[i] - minute + 60;
    if ((hour >= 6 && hour <= 22) || (hour == 23 && minute == 0))
        vehicle_time = minute % 15 + 90;
    else {
        if (hour < 6)
            vehicle_time = (6 - hour) * 60 - minute + 90;
        else
            vehicle_time = (6 + 24 - hour) * 60 - minute + 90;
    }
    if (school_bus_time <= vehicle_time){
        totminutes += school_bus_time;
        return QString::fromStdString("校车");
    }
    else {
        totminutes += vehicle_time;
        return QString::fromStdString("公交车");
    }
}

QStringList graph::dijkstra(int st, int ed, double &totminutes, int mod){
    qDebug()<<st<<ed;
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= VecNum; i++) dis[i]=1e9;
    dis[st] = 0;
    for (int i = 1; i <= VecNum; i++){
        double mindis=1e9;
        int id = 0;
        for (int j = 1; j <= VecNum; j++)
            if (mindis > dis[j] && !vis[j]){
                mindis = dis[j];
                id = j;
            }
        vis[id] = 1;
        if (id == ed) break;
        for (int j = head[id]; j; j = e[j].last){
            double len;
            if (mod == 0) len = e[j].len / (10 + onfootspeed);
            else if (mod == 1) len = e[j].len / (10 + onfootspeed * e[j].narrow / 100);
            else len = min(e[j].len / (10 + onfootspeed * e[j].narrow / 100),
                           e[j].len / (5 + bicyclespeed * e[j].narrow / 100));
            if (dis[id] + len < dis[e[j].to]){
                dis[e[j].to] = dis[id] + len;
                lastpos[e[j].to] = id;
            }
        }
    }
    totminutes += dis[ed];
    QStringList ret_list;
    while (ed!=st){
        ed = lastpos[ed];
        ret_list.append(QString::fromStdString(name[ed]));
    }
    return ret_list;
}

void graph::resetnarrow(int *narrowlist, int num, int line_base){
    for (int i = 1 + line_base; i <= num + line_base; i++)
        e[i * 2].narrow = e[i * 2 - 1].narrow = narrowlist[i];
}
