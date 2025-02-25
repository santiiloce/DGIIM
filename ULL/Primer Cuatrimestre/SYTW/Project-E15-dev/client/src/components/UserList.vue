<template>
  <div>
    <h2>Lista de Usuarios</h2>
    <ul>
      <li v-for="user in users" :key="user.email">
        <p>{{ user.name }} - {{ user.email }} - {{ user.role }}</p>
      </li>
    </ul>
    <p v-if="errorMessage" class="error">{{ errorMessage }}</p>

  </div>
</template>

<script lang="ts">
import { defineComponent, onMounted } from 'vue';
import { useUsersStore } from '@/stores/users_store';

export default defineComponent({
  setup() {
    const usersStore = useUsersStore();


    onMounted(() => {
      usersStore.getUsers();
    });

    return {
      users: usersStore.user,
      errorMessage: usersStore.errorMessage,
    };
  },
});
</script>

<style scoped>
.error {
  color: red;
}
</style>
