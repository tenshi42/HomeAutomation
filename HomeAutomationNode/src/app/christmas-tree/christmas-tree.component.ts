import { Component, OnInit } from '@angular/core';
import { HTTPAPIService } from '../httpapi.service';
import { ConstantesService } from '../constantes.service';

@Component({
  selector: 'app-christmas-tree',
  templateUrl: './christmas-tree.component.html',
  styleUrls: ['../baseStyle.css', './christmas-tree.component.css']
})
export class ChristmasTreeComponent implements OnInit {

  constructor(private httpApi: HTTPAPIService, private constantes: ConstantesService) { }

  BASE_DEVICE_PATH = '/ChristmasTree';
  BASE_URL = this.constantes.BASE_API_URL + ':' + this.constantes.BASE_API_PORT + this.BASE_DEVICE_PATH;

  speeds = [1, 2, 3, 4, 5];
  patterns = [1, 2, 3, 4, 5, 6];

  ngOnInit() {
  }

  SetSpeed(speed: number) {
    this.httpApi.get(
      this.BASE_URL + '/SetSpeed/' + speed
    );
  }

  SetPattern(pattern: number) {
    this.httpApi.get(
      this.BASE_URL + '/SetPattern/' + pattern
    );
  }

  Power(state: boolean) {
    this.httpApi.get(
      this.BASE_URL + '/Power/' + (state ? '1' : '0')
    );
  }
}
