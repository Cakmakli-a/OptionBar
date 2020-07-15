#include <QApplication>
#include <QHBoxLayout>

#include "optionbar.hpp"

int main (int argc, char **argv) {
	QApplication app(argc, argv);

	QWidget centralWidget;
	OptionBar optionbar;

	optionbar.setParent(&centralWidget);
	optionbar.addAction(new QAction("Audio"));
	optionbar.addAction(new QAction("Video"));
	optionbar.addAction(new QAction("Podcasts"));
	optionbar.addAction(new QAction("Photos"));

	QVBoxLayout layout;
	layout.setContentsMargins(0, 0, 0, 0);
	layout.setSpacing(0);
	layout.setMargin(0);
	layout.addStretch(1);
	layout.addWidget(&optionbar);

	app.setActiveWindow(&centralWidget);
	centralWidget.setLayout(&layout);
	centralWidget.show();

	return(app.exec());
}

