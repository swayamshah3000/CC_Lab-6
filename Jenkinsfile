pipeline {
    agent any
    stages {
        stage('Checkout') { steps { checkout scm } }
        stage('Build') { steps { sh 'docker build -t backend-app backend/' } }
        stage('Deploy Infrastructure') {
            steps {
                sh '''
                docker rm -f backend1 backend2 nginx-lb || true
                docker run -d --name backend1 backend-app
                docker run -d --name backend2 backend-app
                
                # Using port 8081 to avoid "Port already allocated" errors
                docker run -d --name nginx-lb -p 8081:80 nginx
                
                sleep 2
                docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf
                docker exec nginx-lb nginx -s reload
                '''
            }
        }
    }
}
