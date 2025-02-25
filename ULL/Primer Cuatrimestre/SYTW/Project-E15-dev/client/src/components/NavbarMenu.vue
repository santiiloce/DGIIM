<template>
  <header class="menu-bar">
    <div class="menu-container">
      <nav class="menu">
        <ul>
          <li><img src="./../assets/SM_logo.png" alt="Method Study Logo" class="logo" /></li>
          <li><h1 class="logo-text">Method Study</h1></li>
          <li><router-link to="/">Inicio</router-link></li>
          <li><router-link to="/about">Acerca de </router-link></li>
          <li><a href="#contacto">Contacto</a></li>
          <div class="auth-buttons">
            <ul>
              <!-- Si el usuario está autenticado -->
              <li v-if="auth.isAuthenticated">
                <h3>Bienvenido, {{ auth.name }}</h3>
              </li>
              <li v-else>
                <button @click="handleLogin">Iniciar Sesión</button>
              </li>
              <li v-if="auth.isAuthenticated">
                <button class='logout' @click="handleLogout">Cerrar Sesión</button>
              </li>
              <!-- Si el usuario no está autenticado -->
              <li v-else>
                <button @click="handleRegister">Registrarse</button>
              </li>
            </ul>
          </div>
        </ul>
      </nav>
    </div>
  </header>
</template>
<script lang="ts">
import { defineComponent } from 'vue'
import { useAuthStore } from '@/stores/authstore' // Tu store de autenticación
import { useRouter } from 'vue-router'

export default defineComponent({
  name: 'NavbarMenu',
  setup() {
    const auth = useAuthStore() // Accede al store de autenticación
    const router = useRouter() // Router para navegar entre vistas

    const handleLogin = () => {
      router.push('/login') // Redirige a la página de inicio de sesión
    }

    const handleRegister = () => {
      router.push('/register') // Redirige a la página de registro
    }

    const handleLogout = async () => {
      await auth.logout() // Cierra sesión a través del store
      router.push('/') // Redirige al inicio después de cerrar sesión
    }

    return {
      auth, // Acceso al estado reactivo del store
      handleLogin,
      handleRegister,
      handleLogout,
    }
  },
})
</script>

<style scoped>
.menu-bar {
  background-color: #344e41;
  color: rgba(7, 255, 139, 0.308);
  padding: 10px 20px;
  position: fixed;
  top: 0;
  left: 0;
  z-index: 1000;
  width: 100%;
}

.menu {
  display: flex;
}

.menu-container {
  display: flex;
  height: 60px;
  justify-content: space-between;
  align-items: center;
}

.menu ul {
  list-style: none;
  margin: 0;
  padding: 10;
  display: flex;
}

.menu ul li img.logo {
  margin-right: 10px; /* Ajusta el espacio entre el logo y el texto */
}

.logo {
  height: auto; /* Mantén la proporción */
  width: 50px; /* Ajusta el tamaño según lo necesario */
  object-fit: contain; /* Evita que el logo se distorsione */
  margin-top: 10;
}

.menu ul li h1 {
  margin-top: -6px;
}
.menu ul li {
  margin-left: 30px; /* Reduce el espacio entre los elementos si es necesario */
  margin-top: 0; /* Elimina cualquier desplazamiento vertical */
  height: 60px; /* Asegúrate de que tengan la misma altura que el navbar */
  display: flex;
  align-items: center;
}
.menu ul li a {
  text-decoration: none;
  color: white;
  font-weight: bold;
  line-height: 60px; /* Ajusta la altura del texto al mismo que el navbar */
}

.menu ul li a:hover {
  color: #a3b18a;
  margin-top: 4px;
}

.menu h3 {
  margin-top: 10px;
  font-size: 1.2rem;
}

.auth-buttons button {
  background-color: #507757;
  color: white;
  border: none;
  padding: 6px 10px;
  border-radius: 20px;
  cursor: pointer;
  transition: background-color 0.4s;
  font-size: 0.9rem;
}

.auth-buttons {
  margin-left: 100px;
}

.auth-buttons button:hover {
  background-color: #23352c;
  margin-top: 2px;
}
</style>
