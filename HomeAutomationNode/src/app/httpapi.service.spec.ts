import { TestBed } from '@angular/core/testing';

import { HTTPAPIService } from './httpapi.service';

describe('HTTPAPIService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: HTTPAPIService = TestBed.get(HTTPAPIService);
    expect(service).toBeTruthy();
  });
});
