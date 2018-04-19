#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>

class Cache;

namespace Ui {
class StarterWindow;
}

class StarterWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit StarterWindow(QWidget *parent = 0);
	~StarterWindow();

	bool openDatabase(const QString &filename);

	void setCache(Cache *cache);

private slots:

	void on_openNewButton_clicked();

	void on_listView_doubleClicked(const QModelIndex &index);

	void on_listView_activated(const QModelIndex &index);

protected:

	void dropEvent(QDropEvent *event) override;

	void dragEnterEvent(QDragEnterEvent *event) override;

private:
	Ui::StarterWindow *ui;
	Cache *cache;
};

#endif // STARTERWINDOW_H