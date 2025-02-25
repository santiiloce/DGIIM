<template>
    <div class="subject-creator">
        <h2>Which subject are you going to study?</h2>
        <label for="subject-name">Subject name:</label>
        <input type="text" id="subjectName" v-model="newSubject.name" placeholder="Name of the subject you want to study" />

        <label for="subject-description">Subject description:</label>
        <input type="text" id="subjectDescription" v-model="newSubject.description" placeholder="Introduce the description of the subject" />

        <button @click="saveSubject">Lets start studying!!</button>
    </div>
</template>

<script lang="ts">
import { defineComponent, ref } from 'vue';
import { useSubjectStore } from '@/stores/subjects_store';
import { usePreferencesStore } from '@/stores/userPreferences_store';
import { useRouter } from 'vue-router';

export default defineComponent({
    name: 'SubjectCreator',
    setup() {

        const subjectStore = useSubjectStore();
        const preferencesStore = usePreferencesStore();
        const router = useRouter();
        const newSubject = ref({
            name: '',
            description: ''
        });
        const saveSubject = async () => {
            const subject = await subjectStore.addSubject(newSubject.value)
            sessionStorage.setItem('subjectName', subject.name)
            savePreferences(subject._id)
        }

        const savePreferences = async (subjectId: string ) => {
            const userID = sessionStorage.getItem('userID');
            const methodId = sessionStorage.getItem('methodID');
            

            if(!userID || !methodId) {
                throw new Error('User ID or method ID not found');
            }
            await preferencesStore.addUserPreferences(userID, methodId, subjectId)
            router.push('/timer')

        }
        return { 
            newSubject, 
            saveSubject 
        }
    }
})
</script>

<style scoped>

.subject-creator h2{
  text-align: center;
  margin-bottom: 2rem;
}

label {
  display: block;
  text-align: center;
  margin-bottom: 1rem;
  font-weight: bold;
  color: #83af82;
}

input {
  width: 100%; 
  padding: 0.75rem;
  margin-bottom: 2rem;
  border-color: none;
  border-radius: 10px;
  font-size: 1rem;
  background-color: #353e49;
  outline: none;
  border: none;
  box-shadow: none;
  transition: box-shadow 0.3s ease-in-out;
}

input:focus {
  border-color: #83af82;
  box-shadow: 0px 0px 4px #79ac92;
  outline: none;
  color: #83af82;
  background-color: #282f38;
  box-shadow: 0 0 5px #83af82
}

button {
  width: 40%;
  padding: 10px;
  font-size: 1rem;
  background-color: #344E41; 
  color: white;
  border: none;
  cursor: pointer;
  transition: background-color 0.4s;
  border-radius: 50px;
  text-align: center;
  margin-top: 2rem;
  display: block;
  margin-left: auto;
  margin-right: auto;
}

button:hover {
  background-color: #23352c;
}

</style>