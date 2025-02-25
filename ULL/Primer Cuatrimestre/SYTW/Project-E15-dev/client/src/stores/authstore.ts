import { defineStore } from 'pinia';
import axios from 'axios';
import { useTimerStore } from './timer_store';

export interface AuthState { 
    email: string | undefined;
    name: string | undefined
    token: string | undefined; 
    isAuthenticated: boolean; 
}

export const useAuthStore = defineStore('auth', {
    state:():AuthState => ({
        email: undefined,
        token: undefined,
        isAuthenticated: false,
        name: undefined
    }),

    actions: {
        async login(email: string, password: string): Promise<void> {
            // Validar que email y password no estan vacíos
            if (!email || !password) {
                throw new Error("Email y contraseña son requeridos");
            }
            try {
              // Enviar solicitud al backend
                const response = await axios.post('http://localhost:5300/user/login', { email, password });
                this.token = response.data.token;
                this.email = response.data.email; 
                this.name = response.data.name;
                const userId = response.data.userID;
                sessionStorage.setItem('loggedUserId', userId);
                if (this.token) {
                    this.isAuthenticated = true;
                    localStorage.setItem('token', this.token);
                    axios.defaults.headers.common['Authorization'] = `Bearer ${this.token}`;
                    return;
                } else {
                    throw new Error("Error al iniciar sesión: El servidor no devolvió un token");
                }
            } catch (error: Error | unknown) {
                if (axios.isAxiosError(error) && error.response?.data) {
                    throw new Error(error.response.data.message || "Error en el servidor");
                } else if (error instanceof Error) {
                    throw new Error(error.message || "Error desconocido");
                } else {
                    throw new Error("Error en el servidor desconocido");
                }
            }
        },

        async logout() {
            const timerStore = useTimerStore();
            timerStore.resetTimer();

            this.email = undefined;
            this.token = undefined;
            this.isAuthenticated = false;
            this.name =undefined

            // Eliminar token del localStorage
            localStorage.removeItem('token');
            sessionStorage.removeItem('loggedUserId');
            delete axios.defaults.headers.common['Authorization'];

            console.log("Sesión cerrada");
        },
    },

    getters: {
        isLoggedIn: (state) => state.isAuthenticated,

        loggedUserId: (): string | null => {
            return sessionStorage.getItem('loggedUserId');
        }
    },
});