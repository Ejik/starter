#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QProcess>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString name(argv[0]);
    QString starterText = "starter.exe";


    if (name.indexOf(starterText) == -1)
    {
        printf("%s", "Ошибка в строке параметров");
        QCoreApplication::exit(1);
        return 1;
    }

    QString cmdLine;

    for (int i = 1; i < argc; i++)
    {
        cmdLine += argv[i];
        cmdLine += " ";
    }
    cmdLine.remove(cmdLine.lastIndexOf(" "), 1);

    // разберем параметры
    QStringList cmdList = cmdLine.split("|");

    QStringListIterator it(cmdList);
    while (it.hasNext())
    {
        QStringList args = it.next().split(" ");
        QString program = args.takeFirst();
        QProcess p;

        p.start(program, args);

        while (!p.waitForFinished())
        {
        }
    }



    QCoreApplication::quit();
    return 0;
    //return a.exec();
}
