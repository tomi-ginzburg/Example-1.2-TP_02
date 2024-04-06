#include "mbed.h"
#include "arm_book_lib.h"

// El ejemplo prende el led 1 si el pin d2 esta en alto (se detecta gas) o si el d3 esta en alto (detecta sobretemperatura)

int main()
{
/* En primera instruccion creo un objeto asociado al pin D2 de la clase DigitalIn
 * La clase DigitalIn utiliza la funcion gpio_init_in a la que le pasa como parametros un tipo de dato gpio junto con el pin D2
 * Luego se llama a gpio_init_in_ex para establecer el modo del pin segun el default
 * A su vez dicha funcion llama a _gpio_init_in que se encarga de llamar a tres funciones
 * 1- gpio_init: inicializa el pin gpio (llena la estructura de datos gpio) 
 * 2- gpio_dir: setea la direccion del pin (le indica que es input)
 * 3- gpio_mode: setea el modo (en este caso el default porque al crear el objeto no se especifico)
 */
   DigitalIn gasDetector(D2);
   
   DigitalIn overTempDetector(D3);
   
   /* Para crear un objeto de la clase DigitalOut se ejecuta de forma similar que DigitalIn
    * Se utilizan otras funciones tal que
    * - la direccion se indique que es output
    * - se inicialice la salida en 0
    */
   DigitalOut alarmLed(LED1);

   /* Para cambiar el modo de conexion del pin asociado se llama al metodo mode de la clase DigitalIn
    * A su vez, el metodo utiliza la funcion gpio_mode(mbed) que utiliza la funcion pin_mode(mbed) 
    * pin_mode utiliza la funcion stm_pin_PullConfig (tambien de mbed)
    * Que a su vez usa LL_GPIO_SetPinPull (libreria de ST)
    * Finalmente se usa la macro MODIFY_REG(de ST) para modioficar el registro PUPDR(GPIO port pull-up/pull-down register,  Address offset: 0x0C)
    */
   gasDetector.mode(PullDown);   
   overTempDetector.mode(PullDown);

   while (true) {
      
      if ( gasDetector || overTempDetector ) {
         
         /* Lo que se esta haciendo al usar el operador = es utilizar el metodo write de la clase DigitalOut
          * Este a su vez usa la funcion gpio_write que directamente escribe sobre los registros para poner los valores correspondientes en la salida del pin
          */
         alarmLed = ON;
      } else {
         alarmLed = OFF;
      }
   }
}