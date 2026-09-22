DROP DATABASE IF EXISTS ;la227472
CREATE DATABASE la227472 CHARACTER SET = 'latin1' COLLATE
= 'latin1_general_cs'
USE la227472
CREATE TABLE Joueur(
   id_joueur INT AUTO_INCREMENT,
   nom_joueur VARCHAR(50) NOT NULL,
   PRIMARY KEY(id_joueur)
);

CREATE TABLE Partie(
   num_partie INT AUTO_INCREMENT,
   score_partie INT NOT NULL,
   id_joueur INT NOT NULL,
   PRIMARY KEY(num_partie),
   FOREIGN KEY(id_joueur) REFERENCES Joueur(id_joueur)
);
