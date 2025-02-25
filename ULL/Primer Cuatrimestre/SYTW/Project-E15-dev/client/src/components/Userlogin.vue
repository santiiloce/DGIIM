<template>
  <main class="main-container">
    <div class="login-container mt-5">
    <form class="login-form card p-4 shadow" @submit.prevent="handleSubmit">
      <h2>Sign In</h2>
      <div class="form-group">
        <label for="email" class="form-label">Email</label>
        <input
          type="email"
          id="email"
          v-model="email"
          placeholder="Introduce your email address"
        />
        </div>
        <div class="form-group">
          <label for="password" class="form-label">Password</label>
          <input
            type="password"
            id="password"
            v-model="password"
            placeholder="Introduce your password"
          />
        </div>
        <button type="submit">Iniciar seción</button>
        <p v-if="errorMessage">{{ errorMessage }}</p>
      </form>
    </div>
  </main>

</template>

<script lang="ts">
import { defineComponent, ref } from 'vue';
import { useAuthStore } from '@/stores/authstore';
import { useRouter } from 'vue-router';
export default defineComponent({
  name: 'UserLogin',
  setup() {
    const email = ref('');
    const password = ref('');
    const errorMessage = ref<string | null>(null);
    const router = useRouter()
    const authStore = useAuthStore();

    const handleSubmit = async () => {
      try {
        await authStore.login(email.value, password.value);
        sessionStorage.setItem('userEmail', email.value);
        router.push('/method-selection');
      } catch (error) {
        console.error("Error desconocido al iniciar sesión", error)
        if(error instanceof Error)
          errorMessage.value = error.message
        alert(errorMessage.value);
      }
    };

    return { email, password, errorMessage, handleSubmit };
  },
});
</script>

<style scoped>
.card {
  width: 150%;
  max-width: 500px;
  border-radius: 20px;
  border-color: #151B23;
  background-color: #1f2731;
  margin: 0 auto;
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
  background-color: #353e49;
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1); 
}

form div {
  margin-bottom: 10px;
}

form label {
  font-size: 0.9rem; 
  font-weight: 600; 
  color: #588157;
  display: block; 
  margin-bottom: 0.5rem; 
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
  border-color: none;
  border-radius: 10px;
  font-size: 1rem;
  background-color: #353e49;
  outline: none;
  border: none;
  box-shadow: none;
  transition: box-shadow 0.3s ease-in-out;
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
  box-shadow: 0 0 5px #83af82
}

.form-group input {
  width: 100%;
  padding: 10px;
  font-size: 14px;
  border: 1px solid #ccc;
  border-radius: 5px;
  box-sizing: border-box;
}

form button {
  width: 100%;
  padding: 10px;
  font-size: 1rem;
  background-color: #344E41; 
  color: white;
  border: none;
  cursor: pointer;
  transition: background-color 0.4s;
  border-radius: 50px;
  text-align: center;
}

button:hover {
  background-color: #23352c;
}
</style>
