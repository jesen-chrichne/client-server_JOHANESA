#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <dirent.h>

void show_files(char* chemin);
void show_file(char* chemin);

int main() {

	
	char message[256], fichier[256]; 
	message = "Bienvenue sur le serveur";
	show_file(".",fichier);

	//initialisation du socket serveur 
	int serv_socket;
	serv_socket = socket(AF_INET,SOCK_STREAM,0);
	
	//declaration des variables pour les adresses
	struct sockaddr_in server_address,cli_addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);

	//Remplissage des informations de l'adresse serveur
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080); //port 8080
	server_address.sin_addr.s_addr = INADDR_ANY;//adresse par defaut

	//liaison du socket serveur sur le port et l'addresse
	int status = bind(serv_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	
	if (status != 0){
		printf("Erreur de l'initialisation du serveur \n");
		return -1;
	}

	
	// mise en ecoute du serveur
	listen(serv_socket, 5);
	int client_socket = accept(serv_socket,(struct sockaddr*) &cli_addr, &addr_size);
	
	printf("Adresse du client: %s \n",inet_ntoa((struct in_addr) cli_addr.sin_addr));
	printf("Socket: %d \n", client_socket);
	printf("Ouverture du dossier... \n");
	
	//envoie du message de bienvenue 
	send(client_socket, message, sizeof(message),0);

	
	//envoie de la liste des documents
	

	//fermeture du socket serveur
	int rc = close(serv_socket);

	return 0;
	
}



}

void show_file(char* chemin,char* nom_fichier){
  DIR *d;
  struct dirent *dir;
  d = opendir(chemin);
  if (d) {
    if ((dir = readdir(d)) != NULL) {
      nom_fichier = dir->d_name;
    }
    closedir(d);
}

}
