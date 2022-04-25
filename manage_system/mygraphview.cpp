#include "mygraphview.h"

using namespace std;

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
    maingraph = new graph();

    QTime randomTime;
    randomTime = QTime::currentTime();
    srand(randomTime.msec()+randomTime.second()*1000);

    ReadFromFile();
}

void myGraphView::mousePressEvent(QMouseEvent *event)
{
    if (event -> button() == Qt::LeftButton)
        onLeftbotton = 1;
}

void myGraphView::mouseReleaseEvent(QMouseEvent *event)
{
    if (onLeftbotton){
        onLeftbotton = 0;
        addVec(mapToScene(event -> pos()), "test");
    }
}

myGraphVectex* myGraphView::addVec(QPointF center, QString name, qreal radius)
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

void myGraphView::ReadFromFile(){
    //vexes
    fstream ts("map.txt", ios::in);
    ts >> VecCnt;
    int x,y,r;
    char S[105];
    for (int i = 0; i < VecCnt; i++){
        ts>>x>>y>>r>>S;
        addVec(QPointF(x, y), QString::fromStdString(S), r);
        maingraph -> addVec(S);
    }
    ts >> EdgeCnt;
    for (int i = 0; i < EdgeCnt; i++){
        ts>>x>>y;
        addLine(vexes[x], vexes[y]);
        maingraph -> addEdge(x + 1, y + 1,
                             dis(vexes[x]->getX(), vexes[x]->getY(),
                                 vexes[y]->getX(), vexes[y]->getY()));
    }
    GetNewNarrow();
    ts.close();
}

double myGraphView::dis(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void myGraphView::GetNewNarrow(){
    for (int i=0; i < line.size(); i++)
        line[i]->ReflashNarrow();
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

void myGraphEdge::ReflashNarrow(){
    Narrow = rand() % 100;
    if (Narrow <40)
        curPen.setColor(smoothColor);
    else if (Narrow < 80)
        curPen.setColor(normalColor);
    else curPen.setColor(crowdColor);
    refreshLine();
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

QStringList graph::FindPath(QStringList guide_list){
    int list[15];
    int size = guide_list.size();
    if (size <= 1) return guide_list;
    QStringList result_list;
    for (int i = 0; i < size; i++)
        list[i] = graphtrie.findid(guide_list[i].toStdString().c_str());
    result_list << QString::fromUtf8(name[list[0]]);
    for (int i = 1; i < size; i++)
        result_list += dijkstra(list[i], list[i-1]);
    qDebug()<<"???"<<result_list;
    return result_list;
}

QStringList graph::dijkstra(int st, int ed){
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
        qDebug()<<id<<" "<<name[id];
        if (id == ed) break;
        for (int j = head[id]; j; j = e[j].last)
            if (dis[id] + e[j].len < dis[e[j].to]){
                dis[e[j].to] = dis[id] + e[j].len;
                lastpos[e[j].to] = id;
            }
    }
    QStringList ret_list;
    while (ed!=st){
        ed = lastpos[ed];
        ret_list.append(QString::fromUtf8(name[ed]));
    }
    return ret_list;
}
