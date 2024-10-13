#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

#include <vector>


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    std::vector<std::pair<std::string, std::string>> contacts;
    int indexCount;

    MainWidget(QMainWindow *parent = nullptr): QWidget(parent)
    {
        indexCount = 1;
        grid = new QGridLayout();
        grid->setSpacing(5);

        name = new QLabel("Name: ");
        nameE = new QLineEdit("");
        nameE->setStyleSheet("border: 1px solid grey");

        number = new QLabel("Phone number: ");
        numberE = new QLineEdit("");
        numberE->setStyleSheet("border: 1px solid grey");

        insert = new QPushButton("insert");
        del = new QPushButton("delete");
        del->setDisabled(true);

        widget1 = new QWidget();
        bar = new QHBoxLayout();
        leftArr = new QPushButton("<");
        leftArr->setDisabled(true);
        index = new QLabel("1");
        index->setStyleSheet("QLabel { qproperty-alignment: 'AlignCenter'; }");
        rightArr = new QPushButton(">");
        rightArr->setDisabled(true);

        bar->addWidget(leftArr);
        bar->addWidget(index);
        bar->addWidget(rightArr);
        widget1->setLayout(bar);

        output = new QLabel();
        output->setStyleSheet("border: 1px solid grey");

        connect(insert, SIGNAL(clicked()), this, SLOT(insertElement()));
        connect(leftArr, SIGNAL(clicked()), this, SLOT(showPrevElement()));
        connect(rightArr, SIGNAL(clicked()), this, SLOT(showNextElement()));
        connect(del, SIGNAL(clicked()), this, SLOT(deleteElement()));

        grid->addWidget(name, 0, 0);
        grid->addWidget(nameE, 0, 1);
        grid->addWidget(number, 1, 0);
        grid->addWidget(numberE, 1, 1);
        grid->addWidget(insert, 2, 0);
        grid->addWidget(del, 2, 1);
        grid->addWidget(widget1, 3, 0, 1, 2);
        grid->addWidget(output, 4, 0, 1, 2);

        setLayout(grid);
    }
    ~MainWidget()
    {
        delete output;
        delete rightArr;
        delete index;
        delete leftArr;
        delete bar;
        delete widget1;
        delete del;
        delete insert;
        delete numberE;
        delete number;
        delete nameE;
        delete name;
        delete grid;
    }
private slots:
    void insertElement() {
        std::pair<std::string, std::string> elem;
        if(nameE->text().toStdString() != "" || numberE->text().toStdString() != "")
        {
            for(const auto& iter: contacts) {
                if (iter.first == nameE->text().toStdString() || iter.second == numberE->text().toStdString())
                {
                    output->setText("Invalid input: already exists");
                    return;
                }
            }
            elem.first = nameE->text().toStdString();
            elem.second = numberE->text().toStdString();
            contacts.push_back(elem);
            indexCount++;
            index->setText(QString::number(indexCount));
            output->setText("Insert succesfull");
            if(indexCount > 1) {
                numberE->setText("");
                nameE->setText("");
                leftArr->setDisabled(false);
            }
        } else {
            output->setText("Invalid input: fields empty");
        }
    }

    void showPrevElement() {
        if(indexCount > 1)
        {
            indexCount--;
            index->setText(QString::number(indexCount));
            nameE->setText(QString::fromStdString(contacts[indexCount-1].first));
            numberE->setText(QString::fromStdString(contacts[indexCount-1].second));
            rightArr->setDisabled(false);
            del->setDisabled(false);
            insert->setDisabled(false);
            if(indexCount < 2) {
                leftArr->setDisabled(true);
                insert->setDisabled(true);
            } else {
                insert->setDisabled(true);
            }
        }
        output->setText("");
    }

    void showNextElement() {
        if(indexCount <= (int) contacts.size()+1)
        {
            indexCount++;
            leftArr->setDisabled(false);
            if(indexCount == (int) contacts.size()+1) {
                rightArr->setDisabled(true);
                insert->setDisabled(false);
                nameE->setText("");
                numberE->setText("");
                del->setDisabled(true);
            }
        }
        if(indexCount <= (int) contacts.size()) {
            insert->setDisabled(true);
            nameE->setText(QString::fromStdString(contacts[indexCount-1].first));
            numberE->setText(QString::fromStdString(contacts[indexCount-1].second));
            del->setDisabled(false);
        }
        index->setText(QString::number(indexCount));
        output->setText("");
    }

    void deleteElement() {
        contacts.erase(contacts.begin() + indexCount-1);
        if(indexCount > 1) {
            nameE->setText(QString::fromStdString(contacts[indexCount-2].first));
            numberE->setText(QString::fromStdString(contacts[indexCount-2].second));
            indexCount--;
        } else {
            if((int) contacts.size() >= 1) {
                nameE->setText(QString::fromStdString(contacts[indexCount-1].first));
                numberE->setText(QString::fromStdString(contacts[indexCount-1].second));
            } else {
                nameE->setText("");
                numberE->setText("");
                insert->setDisabled(false);
                del->setDisabled(true);
                leftArr->setDisabled(true);
                rightArr->setDisabled(true);
            }
        }
        index->setText(QString::number(indexCount));
    }

private:
    QGridLayout* grid;

    QLabel* name;
    QLineEdit* nameE;

    QLabel* number;
    QLineEdit* numberE;

    QPushButton* insert;
    QPushButton* del;

    QWidget* widget1;
    QHBoxLayout* bar;
    QPushButton* leftArr;
    QLabel* index;
    QPushButton* rightArr;

    QLabel* output;
};

#endif
