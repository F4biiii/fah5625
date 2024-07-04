#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

#define N 3

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QMainWindow *parent = nullptr): QWidget(parent)
    {
        grid = new QGridLayout();
        grid->setSpacing(1);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                buttons[i][j] = new QPushButton();
                buttons[i][j]->setFixedSize(60, 60);
                resetButton = new QPushButton();
                resetButton->setText("Reset");
                grid->addWidget(buttons[i][j], i, j);
                grid->addWidget(resetButton, 3, 0, 1, 3);
                connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(changeText()));
                connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
            }

        setLayout(grid);
    }

    ~MainWidget()
    {
        delete grid;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                delete buttons[i][j];
    }

private slots:
    void changeText()
    {
        QObject* obj = sender();

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (obj == buttons[i][j] && buttons[i][j]->text() == "")
                    if(turn) {
                        buttons[i][j]->setText("O");
                        turn = !turn;
                    } else {
                        buttons[i][j]->setText("X");
                        turn = !turn;
                    }
        // or shorter: ((QPushButton*) sender())->setText("X");
    }

    void reset()
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                buttons[i][j]->setText("");
        turn = false;
    }

private:
    bool turn = false;
    QGridLayout *grid;
    QPushButton* buttons[N][N];
    QPushButton* resetButton;
};

#endif // MAINWIDGET_H
