#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "vertical_thread.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QMainWindow *parent = nullptr): QWidget(parent)
    {
        labelX = new QLabel("x:");          // QLabels
        labelY = new QLabel("y:");
        labelS = new QLabel("speed:");
        labelH = new QLabel("height:");
        labelO = new QLabel("\n\n\n");

        inputX = new QLineEdit();           // QLineEdits
        inputY = new QLineEdit();
        inputHeight = new QLineEdit();
        inputSpeed = new QLineEdit();

        startButton = new QPushButton("Start", this);   // QPushButton


        inputX->setStyleSheet("border: 1px solid grey");        // grey border
        inputY->setStyleSheet("border: 1px solid grey");        //
        inputHeight->setStyleSheet("border: 1px solid grey");   //
        inputSpeed->setStyleSheet("border: 1px solid grey");    //
        labelO->setStyleSheet("border: 1px solid grey");        //
        labelO->setAlignment(Qt::AlignCenter);                  // center text in lable

        layoutGrid = new QGridLayout(this);                     // create grid, then position widgets
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
        layoutGrid->setSpacing(5);                              // space between widgets

        setLayout(layoutGrid);                                  // apply layout

        vthread = new VerticalThread();                         // create VerticalThread object

        connect(startButton, SIGNAL(clicked()), this, SLOT(startUfo()));                                        // connect signal (button clicked) to slot (startUfo)
        connect(vthread, SIGNAL(stopped(std::vector<float>)), this, SLOT(updateWindow(std::vector<float>)));    // connect signal (stopped) to slot (updateWindow)
    }

    ~MainWidget()
    {
        delete vthread;
        delete layoutGrid;
        delete startButton;
        delete inputSpeed;
        delete inputHeight;
        delete inputY;
        delete inputX;
        delete labelO;
        delete labelH;
        delete labelS;
        delete labelY;
        delete labelX;
    }

private slots:

    void startUfo()
    {
        bool validInputX = true;                        // is inputX valid or not
        bool validInputY = true;                        // is inputX valid or not
        bool validInputH = true;                        // is inputX valid or not
        bool validInputS = true;                        // is inputX valid or not

        float x = inputX->text().toFloat(&validInputX);  // save inputX in x, also save if the input was valid in validInput
        if(!validInputX)
        {
            inputX->setText("error: must be float");        // output error if input was invalid
        }

        float y = inputY->text().toFloat(&validInputY);  // save inputY in y, also save if the input was valid in validInput
        if(!validInputY)
        {
            inputY->setText("error: must be float");        // output error if input was invalid
        }

        float height = inputHeight->text().toFloat(&validInputH);    // save inputHeight in height, also save if the input was valid in validInput
        if(!validInputH)
        {
            inputHeight->setText("error: must be float");               // output error if input was invalid
        }

        int speed = inputSpeed->text().toInt(&validInputS);  // save inputSpeed in speed, also save if the input was valid in validInput
        if(!validInputS)
        {
            inputSpeed->setText("error: must be int");          // output error if input was invalid
        }

        if(validInputX && validInputY && validInputS && validInputH && height > 0 && speed > 0)    // only fly if input was valid
        {
            labelO->setText("\n\n\n");                      // print "\n\n\n" in output box (reset it)
            startButton->setText("Flying");                 // print "Flying" in button
            startButton->setEnabled(false);                 // make button not available

            vthread->startUfo(x, y, height, speed);         // call startUfo with vthread object
        }
    }

    void updateWindow(const std::vector<float> position)
    {
        float x = round(position[0]*100) / 100;             // round value to two decimals (shift the two decimals before the comma, cut everything after the comma and shift the two decimals back)
        float y = round(position[1]*100) / 100;             //
        float z = round(position[2]*100) / 100;             //

        QString output = "Flight completed\nPosition:\n" + QString::number(x) + " | " + QString::number(y) + " | " + QString::number(z);  // combine output stirng
        labelO->setText(output);        // print the string in output box
        startButton->setText("Start");  // print "Start" in button
        startButton->setEnabled(true);  // make button available
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
