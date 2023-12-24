#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QList>
#include <QStringList>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>





 //c'est un classe qui gere la deplacement des cartes en click  .
mouselable::mouselable(QWidget *parent) : QLabel(parent), isDragging(false) {}

void mouselable::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        offset = event->pos();
        emit clicked();
    }

    QLabel::mousePressEvent(event);
}






void mouselable::startAnimation(const QPoint &startPos, const QPoint &endPos)
{
    // Créer une nouvelle animation pour le déplacement
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(1000);  // Durée de l'animation en millisecondes
    animation->setStartValue(QRect(startPos.x(), startPos.y(), width(), height()));
    animation->setEndValue(QRect(endPos.x(), endPos.y(), width(), height()));
    animation->start(QPropertyAnimation::DeleteWhenStopped);

}





MaClasse::MaClasse(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MaClasse)

{


    ui->setupUi(this);
    setStyleSheet("QMainWindow { background-image: url(:/img/cards/green 3.jpg); background-size: 100% 100%; }");





    connect(ui->actionExit,&QAction::triggered,this,&MaClasse::close);
    connect(ui->actionHelp,&QAction::triggered,this,&MaClasse::Help);



   setStyleSheet("QMainWindow { background-image: url(:/img/cards/green 3.jpg) }");
   /*.background-size: 100% 100%;*/
    // Initialize new members
    titleLabel = new QLabel("TWO OR ONE ", this);
    titleLabel->setFont(QFont("Arial", 50));
    titleLabel->setStyleSheet("color: #FF0000;");
    /*titleLabel->setGeometry(350, 50, 400, 50);*/

    // Créez l'animation
    QPropertyAnimation *animation = new QPropertyAnimation(titleLabel, "geometry");
    animation->setDuration(1000); // Durée de l'animation en millisecondes

    animation->setEndValue(QRect(240, 50, 500, 100));  // Position finale (sous forme de cercle)

    // Configurer l'animation pour le cercle
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // Connectez le slot finished de l'animation à une fonction qui crée un masque circulaire
    connect(animation, &QPropertyAnimation::finished, this, &MaClasse::createCircularMask);

    // Démarrer l'animation
    animation->start();
//-------------------------------------
    imageLabel1 = new QLabel(this);

    imageLabel1->setPixmap(QPixmap(":/img/cards/00.gif").scaled(100, 1000, Qt::KeepAspectRatio));
    imageLabel1->setGeometry(400, 150, 200, 200);



//---------------------------------------
    imageLabel2 = new QLabel(this);
    imageLabel2->setPixmap(QPixmap(":/img/cards/21.gif").scaled(100, 1000, Qt::KeepAspectRatio));
    imageLabel2->setGeometry(600, 300, 200, 200);


//--------------------------------------------------
    imageLabel3 = new QLabel(this);
    imageLabel3->setPixmap(QPixmap(":/img/cards/11.gif").scaled(100, 1000, Qt::KeepAspectRatio));
    imageLabel3->setGeometry(200, 300, 200, 200);

//-------------------------------------------------------
    imageLabel4 = new QLabel(this);
    imageLabel4->setPixmap(QPixmap(":/img/cards/30.gif").scaled(100, 1000, Qt::KeepAspectRatio));
    imageLabel4->setGeometry(400, 425, 200, 200);


//------------------------------------------------------
    startButton = new QPushButton("Start", this);
    startButton->setGeometry(375, 370, 150, 50);
    startButton->setFont(QFont("Poor Richard", 27));
    startButton->setStyleSheet("QPushButton {"
                               "   border-radius: 25px;"
                               "   background-color: #FF0000;"
                               "   color: #FFFFFF;"       // Couleur du texte
                               "}");


 // connecter le button Start avec le function StareGame.
    connect(startButton, &QPushButton::clicked, this, &MaClasse::startGame);

}









void MaClasse::Help() {
    QMessageBox:: information(this,"Help","This is a real Moroccan card game , you can try and paly this game with computer.first, computer starts to play, after you play, if the computer plays a card that has the number 1 or 2, a card will decrease by its 10 cards, and if you played with a card that has a number 1 or 2 , a card will be reduced from your 10 cards, if you have played all your cards, then you are won, if the computer has played all its cards, then the computer is won ");
}


void MaClasse::createCircularMask() {


    // Créer un effet de masque circulaire pour le QLabel
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    titleLabel->setGraphicsEffect(opacityEffect);

    // Créer un dégradé radial pour simuler un masque circulaire
    QRadialGradient gradient(titleLabel->rect().center(), 200);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);

    // Appliquer le dégradé en tant que masque à l'effet d'opacité
    QBrush brush(gradient);
    opacityEffect->setOpacityMask(brush);

}

void MaClasse::startGame() {
    titleLabel->hide();
    imageLabel1->hide();
    imageLabel2->hide();
    imageLabel3->hide();
    imageLabel4->hide();
    startButton->hide();

    // Liste des chemins et des noms de carte correspondants

    cardNames <<"carte_1" <<"carte_2"<<"carte_3"<<"carte_4"<<"carte_5"<<"carte_6"<<"carte_7"<<"carte_10"
              <<"carte_11"<<"carte_12"<<"carte_1_1"<<"carte_2_1"<<"carte_3_1"<<"carte_4_1"<<"carte_5_1"
              <<"carte_6_1"<<"carte_7_1"<<"carte_10_1"<<"carte_11_1"<<"carte_12_1"<<"carte_1_2"<<"carte_2_2"
              <<"carte_3_2"<<"carte_4_2"<<"carte_5_2"<<"carte_6_2"<<"carte_7_2"<<"carte_10_2"<<"carte_11_2"
              <<"carte_12_2"<<"carte_1_3"<<"carte_2_3"<<"carte_3_3"<<"carte_4_3"<<"carte_5_3"<<"carte_6_3"
              <<"carte_7_3"<<"carte_10_3"<<"carte_11_3"<<"carte_12_3";


    imagePaths <<":/img/cards/00.gif" <<":/img/cards/01.gif"<<":/img/cards/02.gif"<<":/img/cards/03.gif"
               <<":/img/cards/04.gif"<<":/img/cards/05.gif"<<":/img/cards/06.gif"<<":/img/cards/07.gif"
               <<":/img/cards/08.gif"<<":/img/cards/09.gif"<<":/img/cards/10.gif"<<":/img/cards/11.gif"
               <<":/img/cards/12.gif"<<":/img/cards/13.gif"<<":/img/cards/14.gif"<<":/img/cards/15.gif"
               <<":/img/cards/16.gif"<<":/img/cards/17.gif"<<":/img/cards/18.gif"<<":/img/cards/19.gif"
               <<":/img/cards/20.gif"<<":/img/cards/21.gif"<<":/img/cards/22.gif"<<":/img/cards/23.gif"
               <<":/img/cards/24.gif"<<":/img/cards/25.gif"<<":/img/cards/26.gif"<<":/img/cards/27.gif"
               <<":/img/cards/28.gif"<<":/img/cards/29.gif"<<":/img/cards/30.gif"<<":/img/cards/31.gif"
               <<":/img/cards/32.gif"<<":/img/cards/33.gif"<<":/img/cards/34.gif"<<":/img/cards/35.gif"
               <<":/img/cards/36.gif"<<":/img/cards/37.gif"<<":/img/cards/38.gif"<<":/img/cards/39.gif";





    for (int i = 0; i <cardNames.size(); ++i) {
        QLabel *label = findChild<QLabel*>(cardNames.at(i));

        if (label && i < imagePaths.size()) {
            label->setPixmap(QPixmap(imagePaths.at(i)));
            label->setScaledContents(true);
        }
    }



    playButton = new QPushButton("Play", this);
    playButton->setGeometry(360, 500, 100, 30);
    playButton->setVisible(true);
    /*playButton->setStyleSheet("background-color: #FF0000;");*/
    playButton ->setFont(QFont("timer new roman", 15));
    playButton->setStyleSheet("QPushButton {"
                               "   border-radius: 15px;"
                               "   background-color: #FF0000;"
                               "   color: #FFFFFF;"       // Couleur du texte
                               "}");
    if (playButton) {
        connect(playButton, &QPushButton::clicked, this, &MaClasse::melange);
    }



    // Changer l'arrière-plan
    QPixmap newBackground(":/img/cards/image3.jpeg");  // Remplacez "new_background.jpg" par le chemin de votre nouvelle image
    QString styleSheet = QString("QMainWindow { background-image: url(:/img/cards/image3.jpeg); }");
    setStyleSheet(styleSheet);

    // Redessiner la fenêtre pour appliquer les changements
    update();




}




MaClasse::~MaClasse()
{
    delete ui;
}

  void MaClasse::melange(){




    // Mélanger les cartes

     shuffledIndices.clear();
    for (int i = 0; i < cardNames.size(); ++i) {
        shuffledIndices << i;

    }

    std::random_shuffle(shuffledIndices.begin(), shuffledIndices.end());


    // Cacher le bouton de mélange

  playButton->hide();



    // Mettre à jour les QLabel avec les nouvelles images mélangées

   for (int i = 0; i < shuffledIndices.size(); ++i) {
        int shuffledIndex = shuffledIndices.at(i);
        QLabel *label = findChild<QLabel*>(cardNames.at(i));


      if (label) {
            label->clear();  // Effacer le contenu de la carte


        }
    }

   // Appelle des fonction pour distribuer les cartes juste après la melange

   distribuerCartesJoueur(shuffledIndices.mid(0, 10), 200, 100);
   distribuerCartesOrdinateur(shuffledIndices.mid(10, 10), 200, 400);


   // le buuton pour rèanilisation de jeux
   recommence = new QPushButton("Replay", this);
   recommence->setGeometry(390, 550, 100, 30);
   recommence->setVisible(true);
   /*playButton->setStyleSheet("background-color: #FF0000;");*/
    recommence ->setFont(QFont("timer new roman", 15));
    recommence->setStyleSheet("QPushButton {"
                             "   border-radius: 15px;"
                             "   background-color: #FF0000;"
                             "   color: #FFFFFF;"       // Couleur du texte
                             "}");
   if ( recommence) {
        connect( recommence, &QPushButton::clicked, this, &MaClasse::melange);
   }





  }


  // Définissez la fonction pour supprimer une carte aléatoire
  void MaClasse::supprimerCarteAleatoire() {

        // Sélectionnez une carte aléatoire
        int indexAleatoire = QRandomGenerator::global()->bounded(cartesDeplaceesParJoueur.size());
        QLabel *carteASupprimer = cartesDeplaceesParJoueur.takeAt(indexAleatoire);



        // Supprimez la carte de la mémoire
        delete carteASupprimer;
    }




  void MaClasse::distribuerCartesJoueur(const QList<int> &indicesJoueur, int endX, int endY) {

        cartesDeplaceesCounter = 0;





    for (int i = 0; i < indicesJoueur.size(); ++i) {
        int shuffledIndex = indicesJoueur.at(i);
        mouselable *label = new mouselable(this);

        label->setObjectName(cardNames.at(shuffledIndex));
        label->setPixmap(QPixmap(imagePaths.at(shuffledIndex)));
        label->setScaledContents(true);

        // Position initiale (ajustez selon votre mise en page)
        label->setGeometry(10 + i * 50, 10, 50, 90);
        label->show();

        // Position finale pour l'animation initiale
        QPoint endPos(endX + i * 50, endY);
       // QPoint endPos(endX, endY);
        // Démarrer l'animation initiale
        label->startAnimation(label->pos(), endPos);
        // Ajouter une bordure au label
        //label->setStyleSheet("border: 5px solid black;");


        // Connecter le signal de clic au slot de gestion des clics
        connect(label, &mouselable::clicked, this, &MaClasse::carteJoueurClicked);

        // Ajoutez la carte au layout du conteneur


        // Ajouter la carte à la liste des cartes de joueur
        cartesDeplaceesParJoueur.append(label);
    }

  }

  void MaClasse::carteJoueurClicked(){
    mouselable *carteCliquee = qobject_cast<mouselable*>(sender());
    if (carteCliquee) {

        // Mettre la carte du joueur au-dessus des cartes de l'ordinateur
        carteCliquee->raise();
        // Déplacer la carte au centre
        QPoint destination((width() - carteCliquee->width()) / 2, (height() - carteCliquee->height()) / 2);

        QPropertyAnimation *animation = new QPropertyAnimation(carteCliquee, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(carteCliquee->geometry());
        animation->setEndValue(QRect(destination.x(), destination.y(), carteCliquee->width(), carteCliquee->height()));






        connect(animation, &QPropertyAnimation::finished, [=]() {

            // Vérifier si l'image de la carte est spécifique
           QString imagePath = imagePaths.at(cardNames.indexOf(carteCliquee->objectName()));

            if (imagePath ==":/img/cards/00.gif"||imagePath == ":/img/cards/01.gif" ||imagePath == ":/img/cards/11.gif" ||imagePath == ":/img/cards/10.gif" ||imagePath == ":/img/cards/20.gif"
                ||imagePath == ":/img/cards/21.gif" ||imagePath == ":/img/cards/30.gif" ||imagePath == ":/img/cards/31.gif" ) {

                // Si l'image est spécifique, supprimer une carte aléatoire de la liste
                supprimerCarteAleatoire();

            }



            // Déplacer les cartes de l'ordinateur immédiatement après le clic du joueur
            deplacerCartes();
        });

        animation->start(QPropertyAnimation::DeleteWhenStopped);

        cartesDeplaceesCounter++;

   if (cartesDeplaceesCounter == cartesDeplaceesParJoueur.size()) {
        // Le joueur a gagné
        QMessageBox messageBox;
        messageBox.setWindowTitle("Gagner ");
        messageBox.setText("<font color='green'>Félisitation , vous avez gagné.</font>");
        messageBox.exec();



       }


  }
  }


  void MaClasse::distribuerCartesOrdinateur(const QList<int> &indicesOrdinateur, int endX, int endY) {


   for (int i = 0; i < indicesOrdinateur.size(); ++i)
   {
        int shuffledIndex = indicesOrdinateur.at(i);
         QLabel *label = findChild< QLabel  *>(cardNames.at(shuffledIndex));



        if (label)
        {
            // Créer une nouvelle image pour la carte

            mouselable *nouvelleCarte = new mouselable(this);

            nouvelleCarte->setPixmap(QPixmap(":/img/cards/back.gif"));  // Utiliser le dos de la carte

            nouvelleCarte->setScaledContents(true);



        // Position initiale (ajustez selon votre mise en page)
            nouvelleCarte->setGeometry(10 + i * 50, 10, 50, 90);
            nouvelleCarte->show();

            QPoint endPos(endX + i * 50, endY);
            nouvelleCarte->startAnimation(nouvelleCarte->pos(), endPos);
            cartesObtenuesParOrdinateur.append(nouvelleCarte);


        }
        }

   // Démarrer le déplacement aléatoire après un délai
   QTimer::singleShot(3000, this, &MaClasse::deplacerCartes);

  }


  void MaClasse::deplacerCartes() {


        deplacer();


}

  void MaClasse::deplacer() {
    if (!cartesObtenuesParOrdinateur.isEmpty()) {
         QLabel *carte = cartesObtenuesParOrdinateur.takeAt(QRandomGenerator::global()->bounded(cartesObtenuesParOrdinateur.size()));


        // Générer un chemin d'image aléatoire pour la face de la carte
        QString imagePath = generateRandomFaceImagePath();

        // Animer la carte actuelle
        carte->raise();
        int destinationX = (width() - carte->width()) / 2;
        int destinationY = (height() - carte->height()) / 2;

        QPropertyAnimation *animation = new QPropertyAnimation(carte, "geometry");
        animation->setDuration(2000);
        animation->setStartValue(carte->geometry());
        animation->setEndValue(QRect(destinationX, destinationY, carte->width(), carte->height()));

        // Connectez le slot de fin d'animation pour changer l'image une fois terminée
        connect(animation, &QPropertyAnimation::finished, [=]() {
            // Changer l'image à la face une fois l'animation terminée
            carte->setPixmap(QPixmap(imagePath));
            // Vérifier si le chemin de l'image est égal à celui spécifié
            if (imagePath ==":/img/cards/00.gif"||imagePath == ":/img/cards/01.gif" ||imagePath == ":/img/cards/11.gif" ||imagePath == ":/img/cards/10.gif" ||imagePath == ":/img/cards/20.gif"
                ||imagePath == ":/img/cards/21.gif" ||imagePath == ":/img/cards/30.gif" ||imagePath == ":/img/cards/31.gif" ) {
                // Diminuer une carte de la liste
                diminuerCarte();
            }


        });

        animation->start(QPropertyAnimation::DeleteWhenStopped);


    }
   if (cartesObtenuesParOrdinateur.isEmpty()) {
        // L'ordinateur a gagné
        QMessageBox messageBox;
        messageBox.setWindowTitle("Défaite");
        messageBox.setText("<font color='red'>Désolé, vous avez perdu.</font>");
        messageBox.exec();

  }



  }


QString MaClasse::generateRandomFaceImagePath() {
    // Générer un indice aléatoire pour choisir une image de carte aléatoire
   int randomIndex = QRandomGenerator::global()->bounded(imagePaths.size());



    // Récupérer le chemin d'image correspondant à l'indice aléatoire
    QString imagePath = imagePaths.at(randomIndex);

    return imagePath;
}

void MaClasse::diminuerCarte() {
    if (!cartesObtenuesParOrdinateur.isEmpty()) {
        // Générer un indice aléatoire pour choisir une carte à effacer
        int randomIndex = QRandomGenerator::global()->bounded(cartesObtenuesParOrdinateur.size());

        // Supprimer la carte à l'indice aléatoire
        delete cartesObtenuesParOrdinateur.takeAt(randomIndex);

    }
    else{
        // L'ordinateur a gagné
        QMessageBox messageBox;
        messageBox.setWindowTitle("Défaite");
        messageBox.setText("<font color='red'>Désolé, vous avez perdu.</font>");
        messageBox.exec();
    }
}




