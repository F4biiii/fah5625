#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <string>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QMainWindow *parent = nullptr): QWidget(parent)
    {
        edit = new QLineEdit();
        button = new QPushButton("Click");
        label = new QLabel();
        label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        grid = new QGridLayout();
        grid->addWidget(edit, 0, 0);
        grid->addWidget(button, 0, 1);
        grid->addWidget(label, 1, 0, 1, 2);
        setLayout(grid);
        connect(button, SIGNAL(clicked()), this, SLOT(changeText()));
    }

    ~MainWidget()
    {
        delete grid;
        delete edit;
        delete button;
        delete label;
    }

private slots:
    void changeText()
    {
        label->setText(edit->text());
    }

private:
    QGridLayout *grid;
    QLineEdit *edit;
    QPushButton *button;
    QLabel *label;
    std::string text;
};

#endif // MAINWIDGET_H
