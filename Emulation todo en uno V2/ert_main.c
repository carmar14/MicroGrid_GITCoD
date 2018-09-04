/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'PV_vsi_sf'.
 *
 * Model version                  : 1.64
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 13:48:18 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
 
#include <wiringSerial.h>
#include <stdlib.h> 
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "PV_vsi_sf.h"                 /* Model's header file */
#include "Diesel_csi_sf.h"
#include "control_terciario.h" 
#include "carga_sf.h" 
#include "BIO_csi_sf.h"   
#include "rtwtypes.h"

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
 
 //Variables creadas por el programador
 //------Entradas-------
 //----PV VSI-----
 double ipv=0.0;
 //double vload=0.0;

 //------Salidas--------
 //----PV VSI-----
 double i3=0.0;
 double soc=0.0;
 
 //------Entradas-------
 //-----Diesel csi------
 double Pref_d=0.0;
 double Qref_d=0.0;
 //double Vload=0.0;
 double par=0.0;
 double flujo=0.0;

 //------Salidas--------
 //-----Diesel csi------
 double i2=0.0;
 
  //------Entradas BIO-------
 double vdc=0.0;
 //double vload2=0.0;
 double pref=0.0;
 double qref=0.0;
 //------Salidas BIO--------
 double i1=0.0;
 
 //------Entradas Carga-------
 //double i1i=0.0;
 //double i2i=0.0;
 //double i3i=0.0;

 //------Salidas Carga--------
 double Pm=0.0;
 double Qm=0.0;
 double Vload=0.0;
 
 //------Entradas Control terciario-------
 //double soc=0.0;
 //double Pm=0.0;
 //double Qm=0.0;

 //------Salidas Control terciario--------
 double Pb=0.0;
 double Qb=0.0;
 double Pd=0.0;
 double Qd=0.0;

 //Comunicacion serial
 int fd;
 char buffer[50];
 char buffer2[50];
 int var=0;
 
//===============================================================
//-------Variables para graficar
#include <math.h>
#define NUM_POINTS 100000
char * commandsForGnuplot[] = {"set title \"TITLEEEEE\"", "plot 'data.temp'"};
double xvals[NUM_POINTS];//= {1.0, 2.0, 3.0, 4.0, 5.0};
double yvals[NUM_POINTS];// = {5.0 ,3.0, 1.0, 3.0, 5.0};
FILE * temp;
FILE *	gnuplotPipe;
int i;
//===============================================================
 
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(PV_vsi_sf_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  
  
  //------------------Codigo-----------------------
  
  //----PV VSI-------------------------------------
  //------Entradas-------
  
  ipv=0;//500;   //Proveniente de la fuente de generación PV
  //vload=123; //Proveniente de la carga
  
  set_Idc_PV(ipv);
  set_Vload(Vload);
  

  /* Step the model for base rate */
  PV_vsi_sf_step();

  /* Get model outputs here */
  
  //-------Salidas------
  i3=get_I_pv();
  soc=get_SOC();
  printf("La corriente del inversor 3 es: %3.2f \n",i3);
  printf("El estado de la bateria es: %3.2f \n",soc);
  //----PV VSI-------------------------------------
  
  
  //----------------------Diesel csi---------------------------
  //-------entradas-------------
  Pref_d=Pd;
  Qref_d=Qd;
  
  par=0.1;
  flujo=1000;
  
  
  set_Pref_d(Pref_d);
  set_Qref_d(Qref_d);
  set_Vload3(Vload);
  set_par(par);
  set_flujo(flujo);

  /* Step the model for base rate */
  //printf("empieza diesel \n");
  Diesel_csi_sf_step();
  //printf("termina diesel \n");
  

  /* Get model outputs here */
  //-----salidas-------
  i2=get_I_die();
  printf("La corriente del inversor DIESEL es: %3.2f \n",i2);
  
  //----------------------Diesel csi---------------------------
  
  //-----------------------BIO csi-----------------------------
  //------Entradas-------
  vdc=500;   //Proveniente de la fuente de generación
  
  pref=Pb;  //Proveniente del control terciario
  qref=Qb; //Proveniente del control terciario
  
  set_Vdc_bio(vdc);
  set_Vload2(Vload);
  set_Qref_bio(pref);
  set_Pref_bio(qref);

  /* Step the model for base rate */
  //printf("empieza BIO \n");
  BIO_csi_sf_step();
  //printf("termina BIO \n");
  
  

  /* Get model outputs here */
  //------Salidas--------
  i1=get_I_bio();
  printf("La corriente del inversor BIO es: %3.2f \n",i1);
  //-----------------------BIO csi-----------------------------
  
  //---------------Carga-----------------
  //------- entradas-------------
  //i1=34;
  //i2=62;
  //i3=24;
  
  set_i1(i1);
  set_i2(i2);
  set_i3(i3);
  
  /* Step the model for base rate */
  //printf("empieza Carga \n");
  carga_sf_step();
  //printf("termina Carga \n");

  /* Get model outputs here */
  //----- salidas-------
  Pm=get_Pm();
  Qm=get_Qm();
  Vload=get_Vload();
  printf("La potencia P medida es: %3.2f \n",Pm);
  printf("La potencia Q medida es: %3.2f \n",Qm);
  printf("La tension medida es: %3.2f \n",Vload);
  
  //---------------Carga-----------------
  
  //----------Control 3-------------------
  //-------entradas-------------
  //soc=98;
  //Pm=1700;
  //Qm=3400;
  set_soc(soc);
  set_Pm(Pm);
  set_Qm(Qm);

  /* Step the model for base rate */
  //printf("empieza terciario \n");
  control_terciario_step();
  //printf("termina terciario \n");

  /* Get model outputs here */
  //-----salidas-------
  Pb=get_Pb();
  Qb=get_Qb();
  Pd=get_Pd();
  Qd=get_Qd();
  printf("La potencia Pb es: %3.2f \n",Pb);
  printf("La potencia Pd es: %3.2f \n",Qb);
  printf("La potencia Qb es: %3.2f \n",Pd);
  printf("La potencia Qd es: %3.2f \n",Qd);
  
  //----------Control 3-------------------
  
   
  //-----------Grafica---------------------
  //i+=0.0001;
  //fprintf(temp, "%3.2f %3.2f \n",i,Vload); 
  /*
  if (i<NUM_POINTS){
    	
		xvals[i]=i+0.00001;
		yvals[i]=Vload;//sin(xvals[i]);	 y=0.05*x.^3-10*x.^2+x;	
		fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
		//fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[1]);
		i=i+1;
	}
	
  //-----------Grafica---------------------
  
  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  
  //Grafica
  i=0;
  
  temp = fopen("data.temp", "w");
    
   gnuplotPipe = popen ("gnuplot -persistent", "w");
    
  fprintf(gnuplotPipe,"set grid \n");
  
  //Serial
  fd=serialOpen ("/dev/ttyACM0", 115200);
  if (fd < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
    
  }
  //fprintf ("fd: %d \n", fd) ;
  //while(1);
   
  /* Initialize model */
  PV_vsi_sf_initialize();
  BIO_csi_sf_initialize();
  carga_sf_initialize();
  Diesel_csi_sf_initialize();
  control_terciario_initialize();

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(PV_vsi_sf_M) == (NULL)) && !rtmGetStopRequested
         (PV_vsi_sf_M) && (rtmGetErrorStatus(BIO_csi_sf_M) == (NULL)) && !rtmGetStopRequested
         (BIO_csi_sf_M) && (rtmGetErrorStatus(carga_sf_M) == (NULL)) && !rtmGetStopRequested
         (carga_sf_M) && (rtmGetErrorStatus(Diesel_csi_sf_M) == (NULL)) && !rtmGetStopRequested
         (Diesel_csi_sf_M) && rtmGetErrorStatus(control_terciario_M) == (NULL)){
    rt_OneStep();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  PV_vsi_sf_terminate();
  BIO_csi_sf_terminate();
  carga_sf_terminate();
  Diesel_csi_sf_terminate();
  control_terciario_terminate();
  
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
