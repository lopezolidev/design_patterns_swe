/*
    El patrón de diseño Singleton, restringe a una sola instacia de acceso global a la clase instanciadora. 
    
    El objetivo de este ejercicio es asegurarnos de que existe una sola instancia de la clase y que esta tiene un contador interno.
*/

#include <iostream>
using namespace std;

class Singleton
{

protected: 
    Singleton() = default;
    // el constructor está como protegido para que no sea instanciado fuera de la clase y como default para que solo sea esta la que acceda a la instancia 

public:

    int counter = 0;
    // contador que incrementaremos en el bucle y que podemos manipular

    void increase_value()
    {
        this->counter++;
    }

    static Singleton& get_instance()
    {
        static Singleton instance;
        return instance;
    } 
    // el uso de métodos y variables estáticos los apega a la clase y evita su manipulación. Además variables locales estáticas son "thread safe" lo que significa que múltiples hilos del procesador no crearán mútiples instancias de esta clase
    
    // Investigué y es conocida como "instanciación perezosa", presuntamente porque los recursos como la memoria no son utilizados a menos que sean realmente necesarios  
    
    // como queremos que la existencia de la instancia sea persistente devolvemos una referencia a memoria.

    Singleton (const Singleton&) = delete;
    /*
     con esto estamos evitando crear copias de una instancia de Singleton mediante la eliminación del constructor copia. Así 

        Singleton singleton_random = singleton_1;
        
     Es señalarle de forma explícita al compilador que no incluya esta función en nuestra clase
    */
    
    Singleton (Singleton&&) = delete;
    
    Singleton& operator = (const Singleton&) = delete;
    
    Singleton& operator = (Singleton&&) = delete; 
    
    // por razones similares estamos diciéndole al compilador que no incluya el operador de copia y asignación
};

int main() 
{
    Singleton &singleton_1 = Singleton::get_instance(); 
    // creamos una variable de referencia para observar su comportamiento
    // accedemos al método estático directamente desde la clase

    cout << "singleton_1.counter = " << singleton_1.counter << endl; // 0

    singleton_1.increase_value(); // llamando al método de increase_value

    cout << "singleton_1.counter = " << singleton_1.counter << endl; // 1

    // ahora creemos una "segunda" instancia de Singleton para estudiar la unicidad de este objeto

    Singleton &singleton_2 = Singleton::get_instance();
    // aparentemente parece una segunda instancia. Sin embargo estudiemos su valor de counter

    cout << "singleton_2.counter = " << singleton_2.counter << endl; // 1
    // es el mismo valor de contador que ya tenía nuestra primera instancia de Singleton 

    singleton_1.counter = 0; // reseteamos el counter

    cout << "================= Ejercicio de contador =================" << endl;

    int i = 0;
    while( i < 10)
    {
        cout << "singleton_1.counter = " << singleton_1.counter << endl;
        
        // Singleton::get_instance.increase_value(); ← C++ no nos dá la posibilidad de hacer lo que C# sí puede en esta línea
        
        i++;

        singleton_1.increase_value();
        //incrementamos el valor
    }

    cout << "singleton_1.counter = " << singleton_1.counter << endl; // estado final del contador

    return 0;
}

