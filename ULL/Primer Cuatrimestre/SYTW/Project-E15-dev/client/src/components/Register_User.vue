<template>
  <main class="main-container">
    <div class="container mt-5">
      <form @submit.prevent="registerUser" class="card p-4 shadow" style="max-width: 100%; width: 500px;">
        <h2 class="text-center mb-4">Sign Up</h2>
        <!-- Name -->
        <div class="form-group mb-3">
          <label for="name" class="form-label">Name:</label>
          <input 
            id="name" 
            v-model="userForm.name" 
            type="text"
            class="form-control"
            :class="{ 'is-invalid': errores.name }"
            placeholder="Enter your name" 
            />
          <div class="invalid-feedback">{{ errores.name }}</div>
        </div>
        <!-- Password -->
        <div class="form-group mb-3">
          <label for="password" class="form-label">Password:</label>
          <input 
            id="password"
            v-model="userForm.password"
            type="password"
            class="form-control"
            :class="{ 'is-invalid': errores.password }"
            placeholder="Enter a password"
          />
          <div class="invalid-feedback">{{ errores.password }}</div>
        </div>
        <!-- Email -->
        <div class="form-group mb-3">
          <label for="email" class="form-label">Email:</label>
          <input 
            id="email"
            v-model="userForm.email"
            type="email"
            class="form-control"
            :class="{ 'is-invalid': errores.email }"
            placeholder="Enter your email" 
          />
          <div class="invalid-feedback">{{ errores.email }}</div>
        </div>

        <!-- Rol -->
        <div class="form-group mb-3">
          <label for="role" class="form-label">Rol:</label>
          <select 
            id="role" 
            v-model="userForm.role" 
            class="form-select"
            :class="{ 'is-invalid': errores.role }"
          >
            <option disabled value="">Select your ocupation</option>
            <option value="student">Student</option>
            <option value="teacher">Teacher</option>
            <option value="college">University</option>
            <option value="master">Administrator</option>
          </select>
          <div class="invalid-feedback">{{ errores.role }}</div>
        </div>

        <button type="submit" class="btn btn-primary w-100" :disabled="loading">
          <span v-if="loading" class="spinner-border spinner-border-sm"></span>
          {{ loading ? "Signing Up..." : "Sign Up" }}
        </button>
      </form>
    </div>
  </main>
</template>

<script lang="ts">
import { defineComponent, reactive, ref } from 'vue'
import { useUsersStore } from '@/stores/users_store'

export default defineComponent({
  setup() {
    const userStore = useUsersStore()
    const loading = ref(false);

    const userForm = reactive({
      name: '', 
      email: '',
      role: '',
      password: '',
    })

    const errores = reactive({
      name: '',
      email: '',
      role: '',
      password: '',
    })

    function validarFormulario() {
      let valido = true
      errores.name = ''
      errores.email = ''
      errores.role = ''

      if (!userForm.name) {
        errores.name = 'El nombre es obligatorio.'
        valido = false
      }
      if (!userForm.password) {
        errores.password = 'La contraseña es obligatorio.'
        valido = false
      }
      if (!userForm.email) {
        errores.email = 'El email es obligatorio.'
        valido = false
      } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(userForm.email)) {
        errores.email = 'El email no es válido.'
        valido = false
      }
      if (!userForm.role) {
        errores.role = 'El rol es obligatorio.'
        valido = false
      }

      return valido
    }

    async function registerUser() {
      if (!validarFormulario()) return;

      loading.value = true;
      try {
        await userStore.registerUser(userForm);
        alert("Usuario registrado exitosamente.");
        Object.assign(userForm, { name: "", email: "", password: "", role: "" });
      } catch (err) {
        console.error("Error al registrar usuario:", err);
      } finally {
        loading.value = false;
      }
    }

    return { userForm, errores, registerUser, loading };
  },
})
</script>

<style scoped>

.card {
  width: 100%; 
  max-width: 500px; 
  border-radius: 20px;
  border-color: #151B23;
  background-color: #1f2731;
}

@media (min-width: 768px) {
  .card {
    width: 70%;
  }
}

@media (min-width: 1200px) {
  .card {
    width: 50%; 
  }
}

.container {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  max-width: 400px;
  margin: 0 auto;
  padding: 20px;
  background-color: #151B23;
  border-radius: 8px;
  min-height: 100vh;
  
}

h2 {
  font-size: 1.9rem;
  margin-bottom: 20px; 
  text-align: center;
  font-weight: 540;
  color: #588157;
}

form {
  width: 100%; 
  max-width: 400px;
  margin: 3rem auto; 
  padding: 2rem 1.5rem; 
  border: 1px solid #ddd;
  border-radius: 8px; 
  background-color: #fff;
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1); 
}

form label {
  font-size: 0.9rem; 
  font-weight: 600; 
  color: #588157;
  display: block; 
  margin-bottom: 0.5rem; 
}

.form-container {
  background: #ffffff;
  padding: 20px;
  border-radius: 8px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); 
  width: 100%;
  max-width: 400px; 
  display: flex;
  flex-direction: column;
  gap: 100px;
}

form div {
  margin-bottom: 10px;
}


label {
  display: block;
  margin-bottom: 5px;
  font-weight: bold;
}

input {
  width: 100%; 
  padding: 0.75rem;
  margin-bottom: 1rem;
  border: 1px solid var(--color-border);
  border-radius: 10px;
  font-size: 1rem;
  /* background-color: #151B23; */
  background-color: #353e49;
  
}

input::placeholder {
  color: #151B23;
  opacity: 1;
}

form input:focus {
  border-color: #83af82;
  box-shadow: 0px 0px 4px #79ac92;
  outline: none;
  color: #83af82;
  background-color: #151B23;
}

.form-select {
  width: 100%;
  padding: 0.75rem;
  margin-bottom: 1rem;
  border: 1px solid var(--color-border);
  border-radius: 10px;
  font-size: 1rem;
  color: #4e4e4e;
  background-color: #353e49;
  color: #151B23;
}

form select:focus {
  border-color: #83af82;
  box-shadow: 0px 0px 4px #79ac92;
  outline: none;
}

span.error {
  display: block; 
  font-size: 0.8rem; 
  color: #d9534f; 
  margin-top: -0.5rem; 
  margin-bottom: 0.75rem; 
  font-weight: 500; 
  position: relative;
  top: -5px;
  background-color: #f8d7da; 
  border: 1px solid #f5c6cb; 
  padding: 0.3rem 0.5rem; 
  border-radius: 4px;
}

.invalid-feedback {
  font-size: 0.875rem; 
  color: #dc3545; 
  margin-top: 0.25rem; 
}


form button {
  width: 50px;
  font-size: 0.9rem;
  background-color: #4c7761; 
  color: white;
  border: none;
  cursor: pointer;
  transition: background-color 0.6s;
  border-radius: 50px;
}

button:hover  {
  background-color: #344E41;
  cursor: not-allowed;
  border-color: #83af82;
  box-shadow: 0px 0px 4px #79ac92;
}

</style>
