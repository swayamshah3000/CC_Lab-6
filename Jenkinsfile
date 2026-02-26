pipeline {
    agent any
    stages {
        stage('Checkout') { steps { checkout scm } }
        stage('Build') { steps { sh 'docker build -t backend-app backend/' } }
        stage('Deploy Infrastructure') {
            steps {
                sh '''
                # Create a shared network if it doesn't exist
                docker network create lab-net || true
                
                # Clean up old containers
                docker rm -f backend1 backend2 nginx-lb || true
                
                # Start containers on the shared network
                docker run -d --name backend1 --network lab-net backend-app
                docker run -d --name backend2 --network lab-net backend-app
                docker run -d --name nginx-lb --network lab-net -p 8081:80 nginx
                
                sleep 2
                
                # Copy the config and reload
                docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf
                docker exec nginx-lb nginx -s reload
                '''
            }
        }
    }
}
