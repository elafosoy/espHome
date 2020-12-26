#ifndef PANTALLAMATRIX_H
#define PANTALLAMATRIX_H


#include <MatrizLed.h>

class PantallaMatrix {

  MatrizLed pantalla;

  int m_velocidad = 90; // Milisegundos entre frames 
  int m_brillo = 1; // intensidad entre 0 y 15 (maximo brillo)

  int m_numDisplayMatrix = 3;
  int m_hPos = 0;
  int m_numMatriz=0;
  

public:

  PantallaMatrix(){
    pantalla.begin(D7, D5, D6, m_numDisplayMatrix); // dataPin, clkPin, csPin, numero de matrices de 8x8
    pantalla.rotar(false);
    pantalla.setIntensidad(m_brillo); 
    pantalla.borrar();

  }

  ~PantallaMatrix(){
  }

  void scrollBar(){
    m_hPos++;
    if (m_hPos == 8){      
      pantalla.setLed(m_numMatriz, 7,7, false);  
      m_hPos=0;
      m_numMatriz++;
      if (m_numMatriz > 2){
        pantalla.setLed(2,7,7, false);  
        m_numMatriz = 0;
      }
    } 
    pantalla.setLed(m_numMatriz, m_hPos-1,7, false); // numero de matriz (empezando por 0), fila, columna, estado
    pantalla.setLed(m_numMatriz, m_hPos, 7, true); // numero de matriz (empezando por 0), fila, columna, estado    
  }
 
 
  void write(char *text, bool scroll = false){     
    pantalla.encender();
    pantalla.borrar();
    if (scroll)
      pantalla.escribirFraseScroll(text, m_velocidad);
    else
      pantalla.escribirFrase(text);
  }

  void setBrillo(int brillo){
    m_brillo = brillo;
    pantalla.setIntensidad(m_brillo); 
  }

};

#endif
