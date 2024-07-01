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
        grid->setSpacing(0);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                buttons[i][j] = new QPushButton();
                buttons[i][j]->setFixedSize(60, 60);
                grid->addWidget(buttons[i][j], i, j);
                connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(changeText()));
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
                if (obj == buttons[i][j])
                    buttons[i][j]->setText("X");

        // or shorter: ((QPushButton*) sender())->setText("X");
    }

private:
    QGridLayout *grid;
    QPushButton* buttons[N][N];
};

#endif // MAINWIDGET_H
