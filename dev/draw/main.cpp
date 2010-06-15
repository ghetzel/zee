#include <QtCore>
#include <QtGui>
#include <canvas.h>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);

	QFrame root;
	QHBoxLayout *hl = new QHBoxLayout(&root);
        Canvas c(&root);
	QSlider s(&root);
	QPushButton b("Reset",&root);

	hl->addWidget(&c);
	hl->addWidget(&s);
	hl->addWidget(&b);

	QObject::connect(&s,SIGNAL(valueChanged(int)),&c,SLOT(addValue(int)));
	QObject::connect(&b,SIGNAL(clicked()),&c,SLOT(clear()));

	root.setLayout(hl);
//	root.setFixedWidth(512);
//	root.setFixedHeight(512);
        root.resize(512,512);
	root.move(384,144);
	root.show();

	return app.exec();
}
