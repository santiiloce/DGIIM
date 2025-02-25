# Improvements to be considered
- Diseño de Interfaz: 
    - Aunque funcional, el diseño es básico y podría beneficiarse de frameworks como Bootstrap o Tailwind CSS.
- Falta de funcionalidad Pomodoro: 
    - No se han implementado las características específicas para gestionar el tiempo de estudio.
- Pruebas Limitadas: 
    - Hasta ahora, solo se han realizado pruebas de hashing y autenticación. Se necesita cubrir el frontend y casos más complejos.
- Documentación: 
    - Sería útil agregar un README claro que explique cómo ejecutar la aplicación y cómo contribuir al desarrollo.

- Completar la Autenticación: 
    - Refinar el flujo de registro e inicio de sesión.
    - Proteger rutas backend con middleware de autenticación.
- Diseñar el Temporizador Pomodoro:
    -Crear componentes específicos para gestionar sesiones de estudio y descansos.
- Optimizar Testing:
    - Extender pruebas a todas las funcionalidades principales.
- Mejorar la UI/UX:
    - Introducir un diseño más atractivo con feedback visual para los usuarios.
- Gestor de datos globales: hacer uso de sessionStorage / localStorage 
    - Crear un gestor de datos global para almacenar información relevante del usuario y su sesión de estudio (useriD, metodo_studio, email, etc)
- Mejorar nombres de variables y componentes y ficheros:
    - Asegurarse de que los nombres de variables, componentes y ficheros sean descriptivos y coherentes.
    - Refactorizar el código para mejorar la legibilidad y mantenimiento.
- Centralizar la APIUrl en un fichero de entorno:
    - Crear un fichero de entorno para almacenar la URL de la API y hacer uso de import.meta.env en el proyecto.
    ````ts
            // api.ts
        import axios from 'axios';

        const api = axios.create({
            baseURL: import.meta.env.VUE_APP_API_URL || 'http://localhost:5300',
        });

        export default api;
    ````
- Centralizar errores en un fichero de entorno o en el propio fichero:
    - Crear un fichero de entorno para almacenar los errores y hacer uso de import.meta.env en el proyecto.
    ````ts
        function handleError(err: unknown): string {
            if (axios.isAxiosError(err)) {
                return err.response?.data?.message || 'Error del servidor';
            } else if (err instanceof Error) {
                return err.message;
            }
            return 'Error desconocido';
        }
    ````