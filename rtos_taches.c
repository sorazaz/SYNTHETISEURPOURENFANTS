BaseType_t xTaskCreate(    TaskFunction_t pvTaskCode,
 			                     const char * const pcName,
                           unsigned short usStackDepth,
                           void *pvParameters,
                           UBaseType_t uxPriority,
                           TaskHandle_t *pxCreatedTask );


//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________

//PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC PIC

READ_STACK_SIZE =
MIDI_STACK_SIZE =

MIDI_PRIORITY =
READ_PRIORITY =

//________________________________________________________________________________
//________________________________________________________________________________


//Tâche READ_PITCH
//Lit la valeur du pitch. Le pitch est connecté à une entrée analogique du PIC.

TaskHandle_t xHandleReadPitch = NULL;

BaseType_t xTaskCreate(  TaskReadPitch,
                         “READ_PITCH”,
                         READ_STACK_SIZE,
                         NULL,
                         READ_PRIORITY,
                         &xHandleReadPitch );

//________________________________________________________________________________
//________________________________________________________________________________

//Tâche READ_KEYS

//Lecture GPIO des touches du clavier.

TaskHandle_t xHandleReadKeys = NULL;

BaseType_t xTaskCreate( TaskReadKeys,
                        “READ_KEYS”,
                        READ_STACK_SIZE,
                        NULL,
                        READ_PRIORITY,
                        &xHandleReadKeys );



//________________________________________________________________________________
//________________________________________________________________________________


//Tâche READ_BUTTONS
//Lecture GPIO des boutons de fonctionnalités

TaskHandle_t xHandleReadButtons = NULL;

BaseType_t xTaskCreate( TaskReadButtons,
                        “READ_BUTTONS”,
                        READ_STACK_SIZE,
                        NULL,
                        READ_PRIORITY,
                        &xHandleReadButtons );


//________________________________________________________________________________
//________________________________________________________________________________


//Tâche SEND_MIDI
//Envoi de valeurs via le protocole MIDI du PIC au DsPIC

TaskHandle_t xHandleSend_MIDI = NULL;

BaseType_t xTaskCreate(  TaskSendMIDI,
                         “SEND_MIDI”,
                         READ_STACK_SIZE,
                         NULL,
                         READ_PRIORITY,
                         &xHandleSend_MIDI );

union MSG_MIDI
{
  // message MIDI séparé
  struct {unsigned char type; unsigned char data1; unsigned char data2; unsigned char b4;} b;
  // message MIDI 32 bits
  unsigned long msg_midi;
};


void SendValueMidi()
{
	uint8_t statut;
	uint8_t data1;
	uint8_t data2;

	for(;;){
    	xTaskNotifyWait(0x00,//on attend la notification
    			  ULONG_MAX,
    			  &statut,
    			  portMAX_DELAY);

    	xTaskNotifyWait(0x00,//on attend la notification
    			  ULONG_MAX,
    			  &data1,
    			  portMAX_DELAY);

    	xTaskNotifyWait(0x00,//on attend la notification
    			   ULONG_MAX,
    			   &data2,
    			   portMAX_DELAY);

    	xSemaphoreTake(semaphore_envoieMIDI, portMAX_DELAY);
    	//on demande le mutex pour ne pas couper l'envoi des données

    	SendMidi(statut); //fonction qui envoie la valeur
    	SendMidi(data1);
    	SendMidi(data2);

    	SemaphoreGive(semaphore_Affichage); // on rend le mutex
	}
}

//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________


//DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC DSPIC

RECEIVE_PRIORITY =
RECEIVE_STACK_SIZE =

//Tâche RECEPTION_MIDI

TaskHandle_t xHandleReceptionMIDI = NULL;

BaseType_t xTaskCreate( TaskReceptionMIDI,
                        “RECEPTION_MIDI”,
                        RECEIVE_STACK_SIZE,
                        NULL,
                        RECEIVE_PRIORITY,
                        &xHandleReceptionMIDI );

//________________________________________________________________________________
//________________________________________________________________________________

//Réception des messages MIDI envoyés par le PIC
//Tâche READ_SPI_MEM

TaskHandle_t xHandleReadSPIMem = NULL;

BaseType_t xTaskCreate( TaskReadSPI,
                        “READ_SPI_MEM”,
                        READ_SPI_STACK_SIZE,
                        NULL,
                        READ_SPI_STACK_PRIORITY,
                        &xHandleReadSPIMem  );


//________________________________________________________________________________
//________________________________________________________________________________

//Calcul du son final

TaskHandle_t xHandleReceptionMIDI = NULL;

BaseType_t xTaskCreate( TaskReceptionMIDI,
                        “RECEPTION_MIDI”,
                        RECEIVE_STACK_SIZE,
                        NULL,
                        RECEIVE_PRIORITY,
                        &xHandleReceptionMIDI );

//________________________________________________________________________________
//________________________________________________________________________________

//Tâche ENVOI_CODEC

TaskHandle_t xHandleReceptionMIDI = NULL;

BaseType_t xTaskCreate(  TaskReceptionMIDI,
                         “RECEPTION_MIDI”,
                         RECEIVE_STACK_SIZE,
                         NULL,
                         RECEIVE_PRIORITY,
                         &xHandleReceptionMIDI );
