/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdlib.h"

#define buffer_size 4
#define START 255
#define STOP 254

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define ARM_MATH_CM4
#include "arm_math.h"

#include "stdio.h"
#include "MCUFRIEND_kbv.h"
#include "avatar.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
	struct Avatar avatar;
	struct Obstacle obstacle;

	int gameover = 0;
	volatile int scroll = 0;
	int timer = 0;
	int full_timer = 0;
	int speed = 200;
	uint8_t posy = 0;
	volatile long y = 0;
	int vitesse = 1;
	volatile int val = 0;
	volatile int compte = 0;
	volatile long Score = 0;
	volatile int comparaisons = 0;
	volatile int value = 0;
	uint8_t id_Tx = 0;




volatile unsigned int flag = 0;
volatile unsigned int flag1 = 0;
volatile unsigned int flag2 = 0;
volatile unsigned int hauteur = 0;
volatile unsigned int mesure_2 = 0;
volatile int local_time = 0;

// buffer pour envoyer et recevoir nos donnees
	uint8_t Tx_buffer[]={START,0,0,STOP}; //donnes a envoyer initialises a 0
	
	uint8_t Rx_buffer [buffer_size]; //donnees a recevoir sur 4 bytes
	uint8_t rx_buff_Full;
	uint8_t tx_buff_empty;
	uint8_t POSITION_VAL=0;
	uint8_t ID=0;

	


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
	
void gagnant()
{
	LCD_FillScreen(BLUE);
	LCD_SetRotation(1);
	char buffer[20] = {0};
	sprintf(buffer, "Gagnant !");
	LCD_SetCursor(45, 60);
	LCD_SetTextSize(4);
	LCD_SetTextColor(WHITE, BLUE);
	LCD_Printf(buffer);
	HAL_Delay(5000);
	
	ID = 0;
	id_Tx = 0;
	
	
	
	//initGame(&avatar, &obstacle, full_timer);
	//drawAvatar(&avatar, full_timer);
	
}

// Fonction pour initialiser le menu principale au debut du jeu
void initMenu()
{
	LCD_Begin();
	HAL_Delay(20);
	
	LCD_FillScreen(BLUE);
	LCD_SetRotation(1);
	char buffer[20] = {0};
	sprintf(buffer, "DINO GAME");
	LCD_SetCursor(45, 60);
	LCD_SetTextSize(4);
	LCD_SetTextColor(WHITE, BLUE);
	LCD_Printf(buffer);
	sprintf(buffer, "Starts in 2 seconds");
	LCD_SetCursor(55, 180);
	LCD_SetTextSize(2);
	LCD_Printf(buffer);
	HAL_Delay(2000);
	
}

	
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifndef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


void HAL_SYSTICK_Callback(void) {
	full_timer++;
	timer++;
	y++;

	
	
	if(y%3000 == 0){
			compte++;
	}
	
	
//	if (flag1 == 0){
//		local_time = 0;
//		if(comparaisons<4){  // la fonction qui détermine si la main n'était pas détecter pendant plus de 600ms
//		flag2 = 2;
//			comparaisons=0;
//			
//		}
//		comparaisons = 0;
//	}
	
	if(flag1 == 1){
	local_time++;
	if(local_time%200 == 0){ // on compte le nombre de temps que la main n'est pas detcter
	comparaisons++;
	}
	}
	
	
	if(flag2 == 1){ // on reinitialize les flag et les compteurs
		local_time = 0;
		comparaisons =0;
		flag2 = 0;
		
	
	}
	
	if (timer >= speed){
		scroll = 1;
		timer = 0;
	}
}




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_UART5_Init();
  MX_TIM1_Init();
  //MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	
	
	//Timer du capteur ultrason
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); 
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);
	
	
	initMenu();
	initGame(&avatar, &obstacle, full_timer);
	drawAvatar(&avatar, full_timer);
	
	rx_buff_Full=0; // Buffer vide donc peut recevoir
	tx_buff_empty=1; 
		HAL_UART_Transmit_DMA(&huart5,Tx_buffer, buffer_size); 
		HAL_UART_Receive_DMA(&huart5, Rx_buffer, buffer_size);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4); //Timer utiliser pour La transmission infrarouge

	


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
	
		char buf[80];
		char mot[80];
		

		
		//sprintf(buf,"Distance:%i\r\n",hauteur); //Affichage sur le LCD
		//LCD_SetCursor(0,40); LCD_Printf(buf);
		
		
		Score++;
		
		
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		while(!scroll);
		scroll = 0;
		avatar.previous_posy = avatar.posy; // on sauvegarde la position precedente de l'avatar
		avatar.posy = hauteur; // on designe la position de l'avatar par rapport a la position de la main
		if(avatar.posy > 210)
			avatar.posy =210; // si la position de la main est plus grande que 210 on garde l'avatar dans l'écran
		
		
		if(hauteur == 0){
			avatar.posy = avatar.previous_posy; // on fait en sorte que l'avatar reste a sa dernière position
			flag2 = 2;
			
		}
		if(hauteur!=0){
				flag1 = 0;
			moveObstacle(&obstacle, compte);
			
			}
		if(flag2 == 2){
			posy = avatar.posy; // on sauvegarde la position ou l'avatar était pendant que la main n'était plus détecter
			flag2 = 1;
			
			//obstacle.posy = posy;

		//	LCD_FillRect(obstacle.posx,obstacle.posy,obstacle.width, obstacle.length,obstacle.color);
//				obstacle.posx = 330;
//				obstacle.length = 30*(7);
//				obstacle.width = 15*(7);
//				LCD_FillRect(obstacle.posx,obstacle.posy,obstacle.width, obstacle.length,BLACK);
			//moveObstacle(&obstacle);
				
			}
		if(obstacle.posx+obstacle.width <=0){ // si le dernier obstacle est sortie de l'ecran
			//obstacle.posy = posy;
			//id_Recue = (rand()%7+1);
			//Tx_buffer[2] = id_Recue;
			Tx_buffer[1]= posy; //on envoie la position y a son adversaire
			obstacle.posy = POSITION_VAL;
			//posy = 000;
		
		}
			
		//if(avatar.posy <20)
			//avatar.posy =0;
		
		drawAvatar(&avatar, full_timer); // on dessine l'avatar
		moveObstacle(&obstacle, compte); // on envoie un les obstacles.
		
		if(ID == 1) // l'écran gagnant du joueur.
		{
			gagnant();
			initGame(&avatar, &obstacle, full_timer); // On refait une autre partie du jeu
			drawAvatar(&avatar, full_timer);
				y = 0000; // On reset tous les timers pour remettre le score à 0
				Score = 0000;
				full_timer = 0;
				local_time = 0;
				timer = 0;
				comparaisons = 0;
				compte = 0;
				flag = 0;
				flag1 = 0;
				flag2 = 0;
				avatar.color = WHITE;
			
		}
		
		gameover = lookColision(&avatar, &obstacle); // la fin du jeu
		LCD_SetTextSize(1);
		sprintf(mot,"Score:%i\r\n",full_timer); //Affichage sur le LCD du score qui correspond au temps en ms qui commence apres le initMenu();
		LCD_SetCursor(0,210); LCD_Printf(mot);
		
		
		
		
	
		if (gameover) {
			id_Tx = 1;
			Tx_buffer[2] = id_Tx;
			HAL_Delay(5000);
				initGame(&avatar, &obstacle, full_timer); // On redemarre une autre partie
				drawAvatar(&avatar, full_timer);
				y = 0000; // On reset tous les timers pour remettre le score à 0
				Score = 0000;
				full_timer = 0;
				local_time = 0;
				timer = 0;
				comparaisons = 0;
				compte = 0;
				flag = 0;
				flag1 = 0;
				flag2 = 0;
				avatar.color = WHITE;
		} // on reinitialize tout pour lorsqu'on recommence le jeu
		
		
		sprintf(buf,"y:%i\r\n",posy); //Affichage sur le LCD de la position auquel on envoie un obstacle a l'adversaire
		LCD_SetCursor(0,20); LCD_Printf(buf);
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
* @brief Retargets the C library printf function to the USART.
* @param None
* @retval None
*/
PUTCHAR_PROTOTYPE
{
/* Place your implementation of fputc here */
/* e.g. write a character to the USART2 and Loop until the end
of transmission */
HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
return ch;
}

//Fonction qui permet de faire la transmission UART et de positionner les bonnes valeurs aux bons endroits
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  
	{
		HAL_UART_Receive_DMA(&huart5,Rx_buffer,4);// Tout l'information est donné
		for(int i=0; i<buffer_size; i++){
			if(Rx_buffer[i]==START && Rx_buffer[(i+3)%4]==STOP){
					
					POSITION_VAL=Rx_buffer[(i+1)%4];
					ID=Rx_buffer[(i+2)%4];
					rx_buff_Full=1;// Recoit tous les données
					
				}
		}

	};
	
	//Fonction qui permet dactiver le PMW pour la transmission quand front montant ou descendant
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){ //Gerer linterruption externe de la pin 12
	value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12); //Lire la veleure recue en A12
	
 	if((GPIO_PIN_RESET == value)){ 				//si A12 = 0 donc pwm=1 puisque logique inversee
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);	//Initialise a 38kHz										
	}
	
	else if((GPIO_PIN_SET == value)){		//si A12 = 1 donc pwm =0 puisque logique inversee
		HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_4);	//Initialise a 38khz							
	}
}
	

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) 
	{
		HAL_UART_Receive_DMA(&huart5, Rx_buffer, buffer_size);
		
	};

//fonction permettant au capteur ultrason de mesurer la distance (la hauteur pour ce projet)
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
		int mesure_1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4); //on prend la valeur pour le front montant (initialement), va devenir descendant plus tard
		int mesure_polarite = mesure_1;																		// Pour changer la polarite de la mesure_1 passe du front montant au front descendant
	
		
		if (flag == 0) {
			hauteur = (mesure_1 - mesure_2)/5.882; // Pour avoir la hauteur en mm
			flag = 1;
		}		
// 199999 = valeur periode mentionne dans STM32		
		else if (mesure_1 > mesure_2) // 
			{
				hauteur = ((199999 - mesure_1) + mesure_2)/5.882; // On s'assure que la mesure_1 soit le front descendant et mesure_2 soit le front montant
			} 
		
		if(hauteur > 500) // On limite le capteur ultrason a 500 mm
		{
			hauteur = 0;
			mesure_1 = 0;
			mesure_2 = 0;
		}
		mesure_2 = mesure_polarite; //mesure_2 devient le front montant et par la suite, mesure_1 devient front descendant
		mesure_polarite = 0;
		flag = 0;
	}
}

	
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
