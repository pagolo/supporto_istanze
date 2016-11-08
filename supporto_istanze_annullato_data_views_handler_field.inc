<?php
class supporto_istanze_annullato_data_views_handler_field extends views_handler_field {
  function render($values) {
/*
    static $i = 1;
//    $editabile = ($this->view->name != 'le_mie_istanze' && !($this->view->name == 'istanze_personale' && $this->view->current_display == 'page_1'));
    $value = $this->get_value($values);
    $nid = $values->webform_submissions_node_nid;
    $sid = $values->webform_submissions_node_sid;
    $uid = $values->users_webform_submissions_uid;
    $tid = $values->webform_submissions_node_si_tid;
    $nodo = node_load($nid);
    $nodata = is_null($values->webform_submissions_node_si_tid);
    if (user_access('annullato') &&
        !$nodata
      ) {
      //$ass_array = array();
      //$ass_array['my_checkbox'] = drupal_get_form('supporto_istanze_form_'.$i, $sid, $uid, $nodata? 0 : $tid, $nodata? 0 : $value, 'protocollo');
      //$html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
      $html = '<input type="button" />';
    }
    elseif ($nodata || is_null($value)) {
      $html = '---';
    } else {
      $html = $value;
    }
    ++$i;
    return $html;
*/
return $this->get_value($values);
  }
}
