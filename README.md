# cs2100-list

##  Work
Vamos a implementar una librería de listas (lista simple, lista doble, lista circular  y lista doble circular enlazada) con iteradores, operadores, templates y traits!!! 

# Structure
```
// Node.h
template <typename T>
class Node {
    protected:
        T value;
        Node<T> * next;

    public:
        Node(void){
        }

        ~Node(void){
        }
};

// List.h
template <typename T>
class List {
    protected:
        Node<T> *head;

    public:
        List(List){ 
			// Constructor copia
        }
        
        List(T*){ 
			//Constructor  parametro, 
			//llena una lista a partir de un array
        }

        List(Node<T>*){ 
			//Constructor por parametro, 
			//retorna una lista con un nodo
        }

        List(int){ 
			//Constructor por parametro, 
			//retorna un lista de randoms de tamaño n
        }

        List(void){ 
			//Constructor por defecto
        }

        ~List(void){
        }

		  // Retorna una referencia al primer elemento
        T front(void) = 0; 
        
		  // Retorna una referencia al ultimo elemento
		    T back(void) = 0; 
        
		  // Inserta un elemento al final
        void push_back(const T& element) = 0; 

		  // Inserta un elemento al inicio
        void push_front(const T& element) = 0; 

		  // Quita el ultimo elemento y retorna una referencia
        T& pop_back(void) = 0;

  		  // Quita el primer elemento y retorna una referencia
        T& pop_front(void) = 0;  

		  // Acceso aleatorio
        T& operator[] (const int&) = 0; 
        
		  // la lista esta vacia?
        bool empty(void) = 0; 

		  // retorna el tamaño de la lista
        unsigned int size(void) = 0; 

		  // Elimina toda la lista
        void clear(void) = 0; 

		  // Elimina un elemento en base a un puntero
        void erase(Node<T>*) = 0; 
        
		  // Inserta un elemento  en base a un puntero
        void insert(Node<T>*, const T&) = 0; 

		  // Elimina todos los elementos por similitud
        void remove(const T&) = 0; 

		  // ordena la lista
        List& sort(void) = 0; 

		  // invierte la lista
        List& reverse(void) = 0; 

		  // Imprime la lista con cout
        template<typename __T>
        inline friend std::ostream& operator<<
			(std::ostream& , const List<__T>& ); 
}

// main.cpp
#include <iostream>

int main (int, char*[]){
    return 1;
}


```

## Help!
Usemos el canal de Slack! 

