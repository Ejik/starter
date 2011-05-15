#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QProcess>
#include <QDir>

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
        args.insert(0, "/C");
        //args.insert(0, "cmd.exe");

        QString exeName = "cmd.exe"; //args.takeFirst();


        QString program = QDir::toNativeSeparators(QDir::currentPath() + "\\" + exeName);
        qDebug() << program << args;

        //int exitCode = QProcess::execute(exeName, args);
        //qDebug() << exitCode;

        QProcess p;
        p.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
        p.start(exeName, args);

        p.waitForReadyRead();
        while (!p.waitForFinished(10000))
        {
            //qDebug() << "work!";
            //a.processEvents();
        }

    }


    QCoreApplication::quit();
    return 0;
    //return a.exec();
}
