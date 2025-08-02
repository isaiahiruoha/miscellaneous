from airflow.decorators import DAG
from airflow.sensors.filesystem import FileSensor
from datetime import datetime

with DAG('dag_sensor', start_date=datetime(2021, 1, 1), schedule_interval='@daily', catchup=False, default_args=default_args) as dag:
    
    waiting_for_file = FileSensor(
        task_id='waiting_for_file',
        poke_interval=30,
        timeout=60 * 5,
        mode='reschedule',
        soft_fail=True,
    )
