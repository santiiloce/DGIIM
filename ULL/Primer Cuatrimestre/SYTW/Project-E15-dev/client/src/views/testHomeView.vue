<script setup lang = "ts">
// Import Bootstrap (si aún no está configurado en tu proyecto)
import "bootstrap/dist/css/bootstrap.min.css";
import "bootstrap/dist/js/bootstrap.bundle.min.js";
</script>
<template>
    <div class="bg-subtle">
        <div class="home-page">
            <div class="text-center py-5">
                <div class="container">
                    <h1 class="display-4 fw-bold text-success"> Welcome to StudyMethod</h1>
                    <p class="lead text-secondary">
                        The ultimate tool for students to manage their stuyd time.
                    </p>
                    <div class="mt-4">
                        <RouterLink to="/register" class="btn btn-primary btn-lg me-2">Log In</RouterLink>
                        <RouterLink to="/about" class="btn btn-success  btn-lg">Start</RouterLink>
                    </div>
                </div>
            </div>
        
            <!-- Features Section -->
            <div class="container my-5">
                <h2 class="text-center text-success mb-4">What does StudyMethod offer?</h2>
                <div class="row">
                <!-- Feature 1 -->
                    <div class="col-md-4 text-center">
                        <div class="p-4">
                            <i class="bi bi-clock-history display-3 text-success mb-3"></i>
                            <h5 class="fw-bold">Time Management</h5>
                            <p class="text-muted">
                                Optimize your study sessions with the technique of your choice
                            </p>
                        </div>
                    </div>
                <!-- Feature 2 -->
                <div class="col-md-4 text-center">
                    <div class="p-4">
                        <i class="bi bi-graph-up-arrow display-3 text-success mb-3"></i>
                        <h5 class="fw-bold">Progress Tracking</h5>
                        <p class="text-muted">
                            Visualize your progress and meet your goals faster.
                        </p>
                    </div>
                </div>
                <!-- Feature 3 -->
                    <div class="col-md-4 text-center">
                            <div class="p-4">
                            <i class="bi bi-people-fill display-3 text-success mb-3"></i>
                            <h5 class="fw-bold">Community</h5>
                            <p class="text-muted">
                                Connect with other students and share your experiences.
                            </p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>    
</template>
  

  
  <style scoped>
  /* Puedes agregar estilos personalizados aquí */
  .bg-light {
    background-color: #707070 !important;
  }
  .text-success {
    color: #1b4229 !important;
  }
  </style>
  