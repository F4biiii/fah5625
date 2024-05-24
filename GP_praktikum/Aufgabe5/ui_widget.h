#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "vertical_thread.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QMainWindow *parent = nullptr): QWidget(parent)
    {
        labelX = new QLabel("x:");
        labelY = new QLabel("y:");
        labelS = new QLabel("speed:");
        labelH = new QLabel("height:");
        inputX = new QLineEdit();
        inputY = new QLineEdit();
        inputHeight = new QLineEdit();
        inputSpeed = new QLineEdit();

        startButton = new QPushButton("Start", this);
        labelO = new QLabel("\n\n\n");

        inputX->setStyleSheet("border: 1px solid grey");
        inputY->setStyleSheet("border: 1px solid grey");
        inputHeight->setStyleSheet("border: 1px solid grey");
        inputSpeed->setStyleSheet("border: 1px solid grey");
        labelO->setStyleSheet("border: 1px solid grey");

        layoutGrid = new QGridLayout(this);
        layoutGrid->addWidget(labelX, 0, 0);
        layoutGrid->addWidget(inputX, 0, 1);
        layoutGrid->addWidget(labelY, 1, 0);
        layoutGrid->addWidget(inputY, 1, 1);
        layoutGrid->addWidget(labelH, 2, 0);
        layoutGrid->addWidget(inputHeight, 2, 1);
        layoutGrid->addWidget(labelS, 3, 0);
        layoutGrid->addWidget(inputSpeed, 3, 1);
        layoutGrid->addWidget(startButton, 4, 0, 1, 2);
        layoutGrid->addWidget(labelO, 5, 0, 1, 2);
        layoutGrid->setSpacing(5);

        setLayout(layoutGrid);

        vthread = new VerticalThread();

        connect(startButton, SIGNAL(clicked()), this, SLOT(startUfo()));
    }

    ~MainWidget()
    {
        delete labelX;
        delete labelY;
        delete labelH;
        delete labelS;
        delete layoutGrid;
    }

private slots:

    void startUfo()
    {
        bool validInput = true;

        float x = inputX->text().toFloat(&validInput);
        if(!validInput)
        {
            inputX->setText("error: must be float");
        }

        float y = inputY->text().toFloat(&validInput);
        if(!validInput)
        {
            inputY->setText("error: must be float");
        }

        float height = inputHeight->text().toFloat(&validInput);
        if(!validInput)
        {
            inputHeight->setText("error: must be float");
        }

        int speed = inputSpeed->text().toInt(&validInput);
        if(!validInput)
        {
            inputSpeed->setText("error: must be int");
        }

        labelO->setText("\n\n\n");
        startButton->setText("Flying");
        startButton->setEnabled(false);

        vthread->startUfo(x, y, height, speed);
    }

private:
    QLabel *labelX;
    QLabel *labelY;
    QLabel *labelS;
    QLabel *labelH;
    QLabel *labelO;

    QLineEdit *inputX;
    QLineEdit *inputY;
    QLineEdit *inputHeight;
    QLineEdit *inputSpeed;

    QPushButton *startButton;

    QGridLayout *layoutGrid;

    VerticalThread *vthread;
};


#endif // UI_WIDGET_H
