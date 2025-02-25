import { defineStore } from 'pinia';
import axios from 'axios';
import type { MethodStudyInterfaces } from '@/models/methodstudy_model';
import { MethodStudy } from '@/models/methodstudy_model';
import { ref, computed } from 'vue';


export const useMethodsStore = defineStore('Methods',()=>{
    const methods = ref<MethodStudyInterfaces[]>([]);
    const error = ref<string | null>(null);
    const errorMessage = computed(() => {
        return error.value ? error.value : '';
    });

    async function getMethods(){
        try {
            const apiUrl = import.meta.env.VUE_APP_API_URL || 'http://localhost:5300';
            const response = await axios.get<MethodStudyInterfaces[]>(`${apiUrl}/method`);
            methods.value = response.data.map( (method) => new MethodStudy(method.name, method.description, method.workDuration, method.breakDuration, method._id)) 
            error.value = null;
        }
        catch(err: unknown){
            if(err instanceof Error){
                console.error('Error:', err.message);
                error.value = 'Error getting the list of methods';
            }
        }
    }
    return { methods, errorMessage, getMethods }
});
