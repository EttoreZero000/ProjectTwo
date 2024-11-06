#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <vector>

class Nodo {
public:
    int dato; // Dato del nodo
    QVector<Nodo*> vecinos; // Lista de nodos conectados
    QPoint posicion; // Posición del nodo

    Nodo(int d) : dato(d) {} // Constructor
};

class GrafoWidget : public QWidget {
    QVector<Nodo*> nodos; // Lista de nodos en el grafo
    std::vector<std::vector<int>> adjacencyList; // Lista de adyacencia
    int nodeCount = 33; // Número de nodos

public:
    GrafoWidget() {
        initializeGraph();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);

        // Calcular posiciones de los nodos según el tamaño de la ventana
        int width = this->width();
        int height = this->height() - 60; // Ajustar altura si es necesario
        setNodePositions(width, height);

        // Dibujar las conexiones entre nodos
        painter.setPen(Qt::black);
        for (Nodo* nodo : nodos) {
            for (Nodo* vecino : nodo->vecinos) {
                painter.drawLine(nodo->posicion, vecino->posicion);
            }
        }

        // Dibujar cada nodo (círculo)
        for (Nodo* nodo : nodos) {
            painter.setBrush(Qt::lightGray);
            painter.drawEllipse(nodo->posicion.x() - 10, nodo->posicion.y() - 10, 20, 20);
            painter.drawText(nodo->posicion.x() - 5, nodo->posicion.y() + 5, QString::number(nodo->dato));
        }
    }

    void initializeGraph() {
        // Crear nodos
        for (int i = 0; i < nodeCount; i++) {
            nodos.append(new Nodo(i));
        }

        // Inicializar la lista de adyacencia
        adjacencyList.resize(nodeCount);
        
        // Definir las conexiones usando la lista de adyacencia
        adjacencyList[0] = {1, 3, 4};
        adjacencyList[1] = {0, 2, 4};
        adjacencyList[2] = {1, 4, 5};
        adjacencyList[3] = {0, 4, 6};
        adjacencyList[4] = {0, 1, 2, 3, 5, 6, 7 ,8};
        adjacencyList[5] = {2, 4, 8};
        adjacencyList[6] = {3 ,4 ,7, 10, 14, 15, 16};
        adjacencyList[7] = {4, 6, 8, 16};
        adjacencyList[8] = {4, 5, 7, 11, 16, 17, 18};
        adjacencyList[9] = {10, 13, 14};
        adjacencyList[10] = {6, 9 , 14}; 
        adjacencyList[11] = {8, 12, 18}; 
        adjacencyList[12] = {11, 18, 19};
        adjacencyList[13] = {9,14, 20};
        adjacencyList[14] = {6, 9, 10, 13, 15, 20, 21, 22}; 
        adjacencyList[15] = {6, 14, 16, 22};
        adjacencyList[16] = {6, 7, 8, 15, 17, 22, 23, 24};
        adjacencyList[17] = {8, 16, 18, 24};
        adjacencyList[18] = {8, 11, 12, 17, 19, 24, 25, 26};
        adjacencyList[19] = {12, 18, 26};
        adjacencyList[20] = {13, 14, 21};
        adjacencyList[21] = {14, 20, 22};
        adjacencyList[22] = {14, 15, 16, 21, 23, 27, 28};
        adjacencyList[23] = {16, 22, 24, 28};
        adjacencyList[24] = {16, 17, 18, 23, 25, 28, 29};
        adjacencyList[25] = {18, 24, 26};
        adjacencyList[26] = {18, 19, 25};
        adjacencyList[27] = {22, 28, 30};
        adjacencyList[28] = {22, 23, 24, 27, 29, 30, 31, 32};
        adjacencyList[29] = {24, 28, 32}; 
        adjacencyList[30] = {27, 28, 31}; 
        adjacencyList[31] = {28, 30, 32}; 
        adjacencyList[32] = {28, 29, 31};

        // Inicializar los vecinos de cada nodo basado en la lista de adyacencia
        for (int i = 0; i < nodeCount; i++) {
            for (int vecino : adjacencyList[i]) {
                nodos[i]->vecinos.append(nodos[vecino]);
            }
        }
    }

    void setNodePositions(int width, int height) {
        // Calcular posiciones de los nodos de manera responsiva
        nodos[0]->posicion = QPoint(width * 3 / 8, height / 8); // 0
        nodos[1]->posicion = QPoint(width * 4 / 8, height / 8); // 1
        nodos[2]->posicion = QPoint(width * 5 / 8, height / 8); // 2

        nodos[3]->posicion = QPoint(width * 3 / 8, height * 2 / 8); // 3
        nodos[4]->posicion = QPoint(width * 4 / 8, height * 2 / 8); // 4
        nodos[5]->posicion = QPoint(width * 5 / 8, height * 2 / 8); // 5

        nodos[6]->posicion = QPoint(width * 3 / 8, height * 3 / 8); // 6
        nodos[7]->posicion = QPoint(width * 4 / 8, height * 3 / 8); // 7
        nodos[8]->posicion = QPoint(width * 5 / 8, height * 3 / 8); // 8

        nodos[9]->posicion = QPoint(width * 1 / 8, height * 3 / 8); // 9
        nodos[10]->posicion = QPoint(width * 2 / 8, height * 3 / 8); // 10
        nodos[11]->posicion = QPoint(width * 6 / 8, height * 3 / 8); // 11
        nodos[12]->posicion = QPoint(width * 7 / 8, height * 3 / 8); // 12

        nodos[13]->posicion = QPoint(width * 1 / 8, 2 * height / 4); // 13
        nodos[14]->posicion = QPoint(width * 2 / 8, 2 * height / 4); // 14
        nodos[15]->posicion = QPoint(width * 3 / 8, 2 * height / 4); // 15
        nodos[16]->posicion = QPoint(width * 4 / 8, 2 * height / 4); // 16
        nodos[17]->posicion = QPoint(width * 5 / 8, 2 * height / 4); // 17
        nodos[18]->posicion = QPoint(width * 6 / 8, 2 * height / 4); // 18
        nodos[19]->posicion = QPoint(width * 7 / 8, 2 * height / 4); // 19

        nodos[20]->posicion = QPoint(width * 1 / 8, height * 5 / 8); // 20
        nodos[21]->posicion = QPoint(width * 2 / 8, height * 5 / 8); // 21
        nodos[22]->posicion = QPoint(width * 3 / 8, height * 5 / 8); // 22
        nodos[23]->posicion = QPoint(width * 4 / 8, height * 5 / 8); // 23
        nodos[24]->posicion = QPoint(width * 5 / 8, height * 5 / 8); // 24
        nodos[25]->posicion = QPoint(width * 6 / 8, height * 5 / 8); // 25
        nodos[26]->posicion = QPoint(width * 7 / 8, height * 5 / 8); // 26

        nodos[27]->posicion = QPoint(width * 3 / 8, height * 6 / 8); // 27
        nodos[28]->posicion = QPoint(width * 4 / 8, height * 6 / 8); // 28
        nodos[29]->posicion = QPoint(width * 5 / 8, height * 6 / 8); // 29

        nodos[30]->posicion = QPoint(width * 3 / 8, height * 7 / 8); // 30
        nodos[31]->posicion = QPoint(width * 4 / 8, height * 7 / 8); // 31
        nodos[32]->posicion = QPoint(width * 5 / 8, height * 7 / 8); // 32
    }

public:
    ~GrafoWidget() {
        // Liberar memoria de los nodos
        qDeleteAll(nodos);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    GrafoWidget window;
    window.resize(400, 400);
    window.setWindowTitle("Grafo Simple");
    window.show();
    
    return app.exec();
}
