# Programación III: Proyecto Final (2024-1)

## Integrantes
* Gabriel Vargas Urmeneta
* Sergio Ricce Abregú
* Fabian Capuñay Lluen
* Diego Atoche Rodriguez

### Video:

## Documentación:

### Resumen:
El programa busca una pelicula en una base de datos dado en un archivo csv. El programa deja al usuario registrarse y buscar alguna pelicula en las categorias de:
* Busqueda por nombre
* Busqueda por tag
* Busqueda por sinopsis
* Busqueda por ID

A partir de esto el ususario puede agregar cada pelicula a su lista de ver mas tarde o darle like, con el fin de que el programa le recomiende peliculas en base a sus gustos.

### Objetos:

El programa se basa en multiples objetos utilizados en funciones que nos ayudan a lograr el funcionamiento de nuestro programa. Los objetos utilizados son los siguientes:
#### Peliculas
Peliculas es una estructura que contiene toda la información de cada pelicula extraida del csv, este tiene como metodos un constructor y la funcion mostrar, la cual muestra el titulo y la ID de la pelicula.

#### Info_peli
En Info_peli hay 3 clases que siguen el patron de diseño decorator, pues con ellsa mostramos mas datos especificos de una pelicula, ya que el metodo mostrar() de Peliculas solo muestra el titulo y el ID.

#### InfoBase
Esta clase modifica el metodo mostrar() para mostrar el titulo, el ID y los tags de la pelicula.

#### InfoDecorador
Esta clase es el decorator, el cual nos ayuda a modificar los metodos de mostrar().

#### InfoCompleta
Esta clase es modifica el metodo mostrar para que adicionalmente muestre las sinopsis y la fuente de la sinopsis, de tal manera que se muestre toda la información completa.

#### Database
La clase Database es un singleton que almacena información de películas en vectores estáticos. Proporciona métodos para agregar y eliminar películas, asegurando que solo exista una instancia de la clase en toda la aplicación. Esta clase está diseñada para gestionar una colección de películas, incluyendo sus IDs de IMDB, títulos, sinopsis, etiquetas, información de división y fuentes de sinopsis.
Esta clase tiene el metodo getInstance, el cual crea una instancia con datos predefinidos y un metodo Initialize() el cual inicia la base de datos con vectores estaticos de datos recuperados.
Tambien dispone de una serie de metodos getter para obtener informacion de las peliculas que contiene y metodos para agregar y eliminar peliculas.

#### Usuarios
Usuarios es una estructura abstracta, pues todos sus metodos son virtuales. Sus metodos son utiles pues con estos formamos otras 2 clases.
##### Usuario Real
Este es el usuario común, el cual tiene como atributos un nombre, contrasela, tipo, suspendido y vectores con las peliculas que el usuario agrego a ver mas tarde y me gusta.
Métodos:
+ UsuarioReal(): Constructor por defecto.
+ UsuarioReal(string nombre, string contrasena, string tipo): Constructor con parámetros.
+ void acceder() override: Implementación del método para manejar el acceso del usuario.
+ string getNombre() override: Implementación del método para obtener el nombre del usuario.
+ string getTipo() override: Implementación del método para obtener el tipo de usuario.
+ string getContrasena() override: Implementación del método para obtener la contraseña del usuario.
+ bool isSuspendido(): Implementación del método para verificar si el usuario está suspendido.
+ void suspender(): Implementación del método para suspender al usuario.
+ void darLike(string peliculaId): Método para marcar una película como "liked".
+ void marcarVerMasTarde(string peliculaId): Método para marcar una película para ver más tarde.
+ void mostrarLikedPeliculas(): Método para mostrar las películas que le gustan al usuario.
+ void mostrarVerMasTardePeliculas(): Método para mostrar las películas marcadas para ver más tarde.

#### UsuarioProxy

La clase UsuarioProxy implementa la interfaz Usuario y actúa como un proxy para UsuarioReal, controlando el acceso al mismo.
Métodos
+ UsuarioProxy(string nombre, string contrasena, string tipo): Constructor con parámetros.
+ bool tieneAcceso(): Método privado para verificar si el usuario tiene acceso.
+ void acceder() override: Implementación del método para manejar el acceso del usuario.
+ string getNombre() override: Implementación del método para obtener el nombre del usuario.
+ string getTipo() override: Implementación del método para obtener el tipo de usuario.
+ string getContrasena() override: Implementación del método para obtener la contraseña del usuario.
+ bool isSuspendido() override: Implementación del método para verificar si el usuario está suspendido.
+ void suspender() override: Implementación del método para suspender al usuario.


#### Admin
La clase Admin hereda de UsuarioReal y añade funcionalidades específicas para administradores.

Métodos
+ Admin(string nombre, string contrasena): Constructor con parámetros.
+ void suspenderUsuario(UsuarioReal& usuario): Método para suspender a otro usuario, si no es administrador.

#### UsuarioManager
UsuarioManager es una clase que se puede tomar como la base de datos de los usuarios, esta tiene como atributos un vector en el que estan guardados los usuarios y otro en donde se guardan los usaurios suspendidos. Los metodos de esta clase son:
+ cargarUsuarios(): Con esta función se cargan los usuarios ya guardados en un csv.
+ agregarUsuario(): Con esta función se agrega una nuevo usuario en la lista de usuarios.
+ guardarUsuario(): Con esta función se guardan los nuevos usuarios en el archivo de csv que guarda a los usuarios.
+ eliminarUsuario(): Con esta función se eliminan usaurios del archivo csv, con el fin que no se quede guardado.
+ getUsuarios(): es un getter con el que obtenemos todos los usuarios.
+ cargarUsuariosSuspendidos(): Con esta función cargamos el csv con los usuarios suspendidos, con el fin de identificarlos.
+ estaSuspendido(): Retorna true o false, dependiendo si el usuario activo esta suspendido o no tiene ninguna restricción.


## Funciones
En el modulo funciones guardamos todas las funciones que implementamos en nuestro proyecto. Las funciones son las siguientes:

#### Split():
Esta función divide un string en base a un separador char dado, luego mete los strings separados en un vector de strings.

#### Split_avanzado():
Esta función es una modificación de split, solo que con pasos extras, de tal manera de que si el separador es un caracter que se repite en un texto que no quieres seprar, evitar ese problema y separarlo de manera correcta.

#### Fill_database():
Llena la base de datos leyendo un archivo CSV y dividiendo sus líneas en subcadenas.

Devuelve: Un vector de vectores de cadenas, donde cada vector interno representa una fila del archivo CSV.

#### Get_col():
Extrae una columna específica de la base de datos.

Parámetros: database - La base de datos representada como un vector de vectores, pos - La posición de la columna a extraer.
Devuelve: Un vector de cadenas que representa la columna extraída.

#### Get_by_column():
Busca películas en la base de datos por una columna específica.

Parámetros: b - Puntero a la base de datos, col - Número de la columna a buscar.
Devuelve: Un vector de objetos Peliculas que coinciden con la búsqueda.

#### Get_peliculas_tag_simple():
Muestra la información básica de las primeras cinco películas en la consola.

Parámetros: peliculas - Vector de objetos Peliculas.

#### Get_peliculas_tag_complejo():
Muestra la información completa de las primeras cinco películas en la consola.

Parámetros: peliculas - Vector de objetos Peliculas.

#### RegistrarUsuario():
Registra un nuevo usuario en el sistema.

Parámetros: manager - Referencia al gestor de usuarios.

#### Login():
Permite a un usuario iniciar sesión en el sistema.

Parámetros: manager - Referencia al gestor de usuarios.
Devuelve: Un puntero a un objeto UsuarioReal si el inicio de sesión es exitoso, nullptr en caso contrario.

#### Interfaz():
Proporciona una interfaz de usuario en la consola para interactuar con la base de datos y gestionar usuarios.

Parámetros: b - Puntero a la base de datos, manager - Referencia al gestor de usuarios.

## Main
Este archivo principal (main.cpp) inicializa y ejecuta la aplicación que gestiona una base de datos de películas y usuarios. La aplicación permite registrar usuarios, iniciar sesión, buscar películas y administrar usuarios suspendidos.

Para el funcionamiento se hace lo siguiente:

Inicialización del UsuarioManager y la Base de Datos:

Se crea una instancia de UsuarioManager que manejará la gestión de usuarios.
Se obtiene la instancia singleton de Database que manejará la base de datos de películas.
Cargar Usuarios desde Archivos CSV:

manager.cargarUsuarios("../usuarios_actualizados.csv"): Carga los usuarios registrados desde un archivo CSV.
manager.cargarUsuariosSuspendidos("../usuarios_suspendidos.csv"): Carga los usuarios suspendidos desde un archivo CSV.
Mostrar la Interfaz:

interfaz(database, manager): Llama a la función interfaz que proporciona una interfaz de usuario en la consola para interactuar con la base de datos y gestionar usuarios.

## Referencias
+ JavaTpoint. (s. f.). CSV file management using C++. Recuperado el 15 de julio de 2024, de https://www.javatpoint.com/csv-file-management-using-cpp
+ Refactoring Guru. (s. f.). Inicio. Recuperado el 15 de julio de 2024, de https://refactoring.guru/es

