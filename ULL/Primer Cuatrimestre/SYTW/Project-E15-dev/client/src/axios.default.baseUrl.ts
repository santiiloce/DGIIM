// api.ts
import axios from 'axios';

const apiURL = axios.create({
    baseURL: import.meta.env.VUE_APP_API_URL || 'http://localhost:5300',
});

export default apiURL;
