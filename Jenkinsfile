pipeline {
    agent any
    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('Build Backend') {
            steps {
                sh 'docker build -t backend-app backend/'
            }
        }
        stage('Deploy Infrastructure') {
            steps {
                sh '''
                # Clean up old containers
                docker rm -f backend1 backend2 nginx-lb || true
                
                # Start Backends
                docker run -d --name backend1 backend-app
                docker run -d --name backend2 backend-app
                
                # Start NGINX without the volume mount
                docker run -d --name nginx-lb -p 80:80 nginx
                
                # Wait 2 seconds for NGINX to initialize
                sleep 2
                
                # Manually copy the config file into the container
                docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf
                
                # Reload NGINX to apply the new config
                docker exec nginx-lb nginx -s reload
                '''
            }
        }
    }
    post {
        success {
            echo 'Pipeline completed successfully!'
        }
    }
}
