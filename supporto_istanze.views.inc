<?php
/**
 * hook for the Views module
 */
/**
 * Implements hook_views_data().
 */ 
function supporto_istanze_views_data() {
  $data = array();
  $data['si']['table']['group'] = 'Supporto istanze';
  $data['si']['table']['join'] = array(
    'webform_submissions' => array(
      'left_field' => 'sid',
      'field' => 'submission_id',
      'table' => 'supporto_istanze',
    ),
  );
  $data['si']['tid'] = array(
    'title' => 'Chiave di istanza',
    'help' => 'Indice primario tabella supporto_istanze.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
  );
  $data['si']['submission_id'] = array(
    'title' => 'Chiave di submission',
    'help' => 'Indice primario tabella webform_submissions.',
    'relationship' => array(
      'base' => 'webform_submissions', // The name of the table to join with.
      'base field' => 'sid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship',
      'label' => 'Relazione supporto_istanze',
      'title' => 'Relazione con la tabella delle Submissions',
      'help' =>'Collega le tabelle webform_submissions e supporto_istanze',
    ),
  );
  $data['si']['protocollo_stato'] = array(
    'title' => 'Protocollo',
    'help' => 'Istanza protocollata.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_protocollo_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
/*
  $data['si']['acquisito_stato'] = array(
    'title' => 'Acquisito',
    'help' => 'Istanza acquisita.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_acquisito_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
*/
  $data['si']['concedibile_stato'] = array(
    'title' => 'Verifica ufficio',
    'help' => 'Istanza concedibile.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_concedibile_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['visto_dsga_stato'] = array(
    'title' => 'Visto DSGA',
    'help' => 'Istanza conforme.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_visto_dsga_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['visto_referente_stato'] = array(
    'title' => 'Visto Referente',
    'help' => 'Istanza conforme.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_visto_referente_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['visto_stato'] = array(
    'title' => 'Visto DS',
    'help' => 'Istanza accolta.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_visto_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['evaso_data'] = array(
    'title' => 'Evaso',
    'help' => 'Istanza evasa il...',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['annullato_data'] = array(
    'title' => 'Annullato',
    'help' => 'Istanza annullata il...',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_annullato_data_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['elaborato_data'] = array(
    'title' => 'Elaborato',
    'help' => 'Istanza finalizzata il...',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_elaborato_data_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['motivazioni'] = array(
    'title' => 'Motivazioni',
    'help' => 'Le motivazioni per il rifiuto della istanza.',
    'table' => 'supporto_istanze',
    'field' => array(
      'handler' => 'supporto_istanze_motivazioni_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['si']['modifica'] = array(
    'title' => 'Modifica istanze',
    'help' => 'Inserire questo campo per permettere la modifica delle istanze.',
    'field' => array(
      'handler' => 'supporto_istanze_modifica_views_handler_field',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function supporto_istanze_views_handlers() {
  return array(
  'info' => array(
    'path' => drupal_get_path('module', 'supporto_istanze'),
    ),
  'handlers' => array(
    'supporto_istanze_modifica_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),
    'supporto_istanze_protocollo_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),
/*        
    'supporto_istanze_acquisito_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),
*/        
    'supporto_istanze_concedibile_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_visto_dsga_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_visto_referente_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_visto_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),
    'supporto_istanze_annullato_data_views_handler_field' => array(
      'parent' => 'views_handler_field_date',
     ),        
    'supporto_istanze_elaborato_data_views_handler_field' => array(
      'parent' => 'views_handler_field_date',
     ),        
    'supporto_istanze_motivazioni_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    ),
  );
}
