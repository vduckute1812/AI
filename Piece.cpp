#include "Piece.h"
#include "Pawn.h"
#include "Board.h"
#include "BoardUntils.h"
#include <QPainter>
#include <QtWidgets>

Piece::Piece(int piecePos, Alliance pieceAlliance, PieceType type, QWidget *parent) :QFrame(parent)
{
	m_piecePosition = piecePos;
	m_pieceAlliance = pieceAlliance;
	m_pieceType		= type;

	setAcceptDrops(true);		// accept Drop

	m_icon = new QLabel(this);
	m_icon->setPixmap(QPixmap(QString("Resources/") + QString(type) + QString(pieceAlliance) + QString(".svg")));
	m_icon->resize(QSize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE));

	hashCodeKeyValue();

	m_icon->setAttribute(Qt::WA_DeleteOnClose);
}

Piece::~Piece()
{
}

void Piece::setPosition(int position)
{
	m_piecePosition = position;
}

int Piece::getPosistion() const
{
	return m_piecePosition;
}

Alliance Piece::getAlliance() const
{
	return m_pieceAlliance;
}

PieceType Piece::getPieceType() const
{
	return m_pieceType;
}

char Piece::getKeyCharacter() const
{
	return m_pieceType;
}

void Piece::hashCodeKeyValue()
{

	std::hash<char> hash_fn;

	const int prime = 31;
	int result = static_cast<int>(hash_fn(m_pieceType));

	result = prime * result + static_cast<int>(hash_fn(m_pieceAlliance));
	result = prime * result + m_piecePosition;

	if (m_pieceType == PieceType::PAWN)
	{
		Pawn* pawn = static_cast<Pawn*> (this);
		result = prime * result + (pawn->isFirstMove() ? 1: 0);
	}

	m_hashCode = result;
}

int  Piece::getHash() const
{
	return m_hashCode;
}

QLabel*	Piece::getRenderImg()
{
	return m_icon;
}

void Piece::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
		if (event->source() == this) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else {
			event->acceptProposedAction();
		}
	}
	else {
		event->ignore();
	}
}

void Piece::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
		if (event->source() == this) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else {
			event->acceptProposedAction();
		}
	}
	else {
		event->ignore();
	}
}

void Piece::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
		QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPixmap pixmap;
		QPoint offset;
		dataStream >> pixmap >> offset;

		QLabel *newIcon = new QLabel(this);
		newIcon->setPixmap(pixmap);
		newIcon->move(event->pos() - offset);
		newIcon->show();
		newIcon->setAttribute(Qt::WA_DeleteOnClose);

		if (event->source() == this) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else {
			event->acceptProposedAction();
		}
	}
	else {
		event->ignore();
	}
}

void Piece::mousePressEvent(QMouseEvent *event)
{
	QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
	if (!child)
		return;

	QPixmap pixmap = *child->pixmap();

	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	dataStream << pixmap << QPoint(event->pos() - child->pos());

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("application/x-dnditemdata", itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(pixmap);
	drag->setHotSpot(event->pos() - child->pos());

	QPixmap tempPixmap = pixmap;
	QPainter painter;
	painter.begin(&tempPixmap);
	painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
	painter.end();

	child->setPixmap(tempPixmap);

	if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
		child->close();
	}
	else {
		child->show();
		child->setPixmap(pixmap);
	}
}