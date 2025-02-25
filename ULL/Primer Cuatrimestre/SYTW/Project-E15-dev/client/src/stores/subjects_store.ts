import { ref, computed } from 'vue'
import { defineStore } from 'pinia'
import type {SubjectInterfaces } from '@/models/subject_model'
import { Subject } from '@/models/subject_model'
import { Types } from 'mongoose';

export const useSubjectStore = defineStore('Subject',()=>{
    const subjects = ref<SubjectInterfaces []>([]);
    const error = ref<string | null>(null);
    const errorMessage = computed(() => {
        return error.value ? error.value : '';
    });

    async function getSubject() {
        const apiUrl = import.meta.env.VUE_APP_API_URL || 'http://localhost:5300'; 
        const response = await fetch(`${apiUrl}/subject`)
        const data = await response.json();
        subjects.value= data.map((subject:SubjectInterfaces)=> new Subject(subject.name, subject.description, subject._id))
    }

    async function addSubject(subjectadd: SubjectInterfaces) {
        const apiUrl = import.meta.env.VUE_APP_API_URL || 'http://localhost:5300';
        const response = await fetch(`${apiUrl}/subject`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(subjectadd)
        });
        const newSubject = await response.json();
        subjects.value.push(newSubject);
        return newSubject;
    }

    async function deleteSubject(id: Types.ObjectId) { 
        const index = subjects.value.findIndex(subject => {if(subject._id)subject._id.equals(id)}); 
        if (index !== -1) { 
            subjects.value.splice(index, 1); 
        } else { 
            console.error("Subject no found"); 
        } 
    }
    function putSubject(id: Types.ObjectId, datosActualizados: Partial<SubjectInterfaces >) { 
        const index = subjects.value.findIndex(usuario => usuario._id?.equals(id)); 
        if (index !== -1) {  
            subjects.value[index] = { ...subjects.value[index], ...datosActualizados }; 
        } else { 
            console.error("Subject no found"); 
        } 
    }
    return {subjects,addSubject,getSubject,putSubject,deleteSubject,errorMessage}
})