#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "Card.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Create test card
    Card card;

    card.name = "Grizzly Bears";
    card.mana_cost = "{1}{G}";
    card.cmc = 2;
    card.types = { type::Creature };
    card.subtype = { "Bear" };
    card.power = 2;
    card.toughness = 2;

    // Create window
    QWidget window;
    window.setWindowTitle("Ponder - Card Test");
    window.resize(400, 300);

    // Create layout
    QVBoxLayout* layout = new QVBoxLayout(&window);

    // Create labels
    QLabel* nameLabel = new QLabel(
        QString::fromStdString(card.name)
    );

    QLabel* manaLabel = new QLabel(
        QString("Mana Cost: %1").arg(QString::fromStdString(card.mana_cost))
    );

    QLabel* cmcLabel = new QLabel(
        QString("CMC: %1").arg(card.cmc)
    );

    QLabel* typeLabel = new QLabel(
        QString("Type count: %1").arg(static_cast<int>(card.types.size()))
    );

    QLabel* subtypeLabel = new QLabel(
        QString("Subtype: %1").arg(
            QString::fromStdString(card.subtype[0])
        )
    );

    QLabel* statsLabel = new QLabel(
        QString("Power/Toughness: %1/%2")
        .arg(*card.power)
        .arg(*card.toughness)
    );

    // Add labels to layout
    layout->addWidget(nameLabel);
    layout->addWidget(manaLabel);
    layout->addWidget(cmcLabel);
    layout->addWidget(typeLabel);
    layout->addWidget(subtypeLabel);
    layout->addWidget(statsLabel);

    window.show();

    return app.exec();
}